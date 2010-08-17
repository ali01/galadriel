#include "code_generator.h"

/* stl includes */
#include <sstream>
using std::stringstream;


/* project includes */
#include <ast_includes.h>
#include <utility.h> // TODO

/* scope includes */
#include <scope_includes.h>

/* local includes */
#include "instruction_includes.h"
#include "location_includes.h"
#include "mips_emit_functor.h"
#include "tac_emit_functor.h"

CodeGenerator::CodeGenerator(Simone::Ptr<Program> _prog) {
  node_functor_ = NodeFunctor::NodeFunctorNew();
  node_functor_(_prog);
  emit_instruction_stream();
}

/* top level */
void
CodeGenerator::NodeFunctor::operator()(Program *nd) {
  Decl::Ptr decl;
  Program::const_decl_iter it = nd->declsBegin();
  for (; it != nd->declsEnd(); ++it) {
    decl = *it;
    process_node(decl);
  }
}


/* decl */
void
CodeGenerator::NodeFunctor::operator()(Decl *nd) {
  Identifier::Ptr id = nd->identifier();
  process_node(id);
}

void
CodeGenerator::NodeFunctor::operator()(VarDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  Type::Ptr type = nd->type();
  process_node(type);
}

void
CodeGenerator::NodeFunctor::operator()(FnDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  Type::Ptr return_type = nd->returnType();
  process_node(return_type);

  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    process_node(decl);
  }

  /* stmt_block could be NULL in the case of a function prototype */
  StmtBlock::Ptr stmt_block = nd->body();

  if (stmt_block) {
    /* BeginFunc instruction */
    In::BeginFunc::Ptr begin_func_i;
    begin_func_i = In::BeginFunc::BeginFuncNew(nd->label());
    process_instruction(begin_func_i);

    /* processing function body */
    process_node(stmt_block);

    /* back patching frame size */
    LocalScope::PtrConst local_scope;
    local_scope = Ptr::st_cast<LocalScope>(stmt_block->scope());
    In::BeginFunc::FrameSize frame_size = local_scope->size();
    begin_func_i->frameSizeIs(frame_size);

    /* EndFunc instruction */
    In::EndFunc::Ptr end_func_i = In::EndFunc::EndFuncNew();
    process_instruction(end_func_i);
  }
}


/* decl/object */
void
CodeGenerator::NodeFunctor::operator()(ObjectDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  Decl::Ptr decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    process_node(decl);
  }
}

void
CodeGenerator::NodeFunctor::operator()(ClassDecl *nd) {
  if (not nd->isLibraryStub()) {
    /* apply this functor to upcasted nd */
    (*this)(static_cast<ObjectDecl*>(nd));

    /* emitting v_table */
    In::VTable::Ptr v_table_i;
    Deque<In::Label::Ptr>::Ptr fn_labels = nd->functionLabels();
    v_table_i = In::VTable::VTableNew(nd->label(), fn_labels);
    process_instruction(v_table_i);
  }
}

void
CodeGenerator::NodeFunctor::operator()(InterfaceDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<ObjectDecl*>(nd));
}


/* stmt */
void
CodeGenerator::NodeFunctor::operator()(StmtBlock *nd) {
  VarDecl::Ptr var_decl;
  StmtBlock::const_decl_iter decl_it = nd->declsBegin();
  for (; decl_it != nd->declsEnd(); ++decl_it) {
    var_decl = *decl_it;
    process_node(var_decl);
  }

  Stmt::Ptr stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    process_node(stmt);
  }
}

void
CodeGenerator::NodeFunctor::operator()(PrintStmt *nd) {
  Expr::Ptr arg;

  /* arg location */
  Location::Ptr loc;

  /* PushParam and LCall instructions */
  In::PushParam::Ptr push_param_i;
  In::Label::PtrConst label_i;
  In::LCall::Ptr l_call_i;

  PrintStmt::const_arg_iterator it = nd->argsBegin();
  for (int i = 1; it != nd->argsEnd(); ++it, ++i) {
    arg = *it;
    process_node(arg);

    /* PushParam */
    loc = arg->location();
    process_location(loc);

    push_param_i = In::PushParam::PushParamNew(loc);
    process_instruction(push_param_i);

    /* label for LCall */
    Type::PtrConst arg_type = arg->type();
    if (arg_type == Type::kInt) {
      label_i = In::Label::kPrintInt;

    } else if (arg_type == Type::kBool) {
      label_i = In::Label::kPrintBool;

    } else if (arg_type == Type::kString) {
      label_i = In::Label::kPrintString;
    }

    l_call_i = In::LCall::LCallNew(label_i, NULL);
    process_instruction(l_call_i);
    process_instruction(In::PopParams::PopParamsNew(1));
  }
}

void
CodeGenerator::NodeFunctor::operator()(ReturnStmt *nd) {
  Expr::Ptr expr = nd->expr();
  process_node(expr);

  Location::Ptr eval_loc;
  if (expr != NULL) {
    eval_loc = expr->location();
    process_location(eval_loc);
  } else {
    eval_loc = NULL;
  }

  In::Return::Ptr return_i = In::Return::ReturnNew(eval_loc);
  process_instruction(return_i);
}

void
CodeGenerator::NodeFunctor::operator()(BreakStmt *nd) {
  // TODO:
}


/* stmt/conditional */

void
CodeGenerator::NodeFunctor::operator()(IfStmt *nd) {
  /* processing test */
  Expr::Ptr test = nd->test();
  process_node(test);

  Location::Ptr test_loc = test->location();
  process_location(test_loc);

  In::Label::Ptr else_label = labelNew();
  In::IfZ::Ptr ifz_i = In::IfZ::IfZNew(test_loc, else_label);
  process_instruction(ifz_i);

  /* processing if_stmt body */
  Stmt::Ptr body = nd->body();
  process_node(body);

  Stmt::Ptr else_body = nd->elseBody();
  if (else_body) {
    /* instructions to skip around else_stmt in case of success */
    In::Label::Ptr endif_label = labelNew();
    In::Goto::Ptr goto_i = In::Goto::GotoNew(endif_label);
    process_instruction(goto_i);

    /* else_stmt label */
    process_instruction(else_label);

    /* processing else_stmt body */
    process_node(else_body);

    /* label used to skip around else_stmt if success */
    process_instruction(endif_label);

  } else {
    /* else_stmt label */
    process_instruction(else_label);
  }
}


/* stmt/conditional/loop */

void
CodeGenerator::NodeFunctor::operator()(ForStmt *nd) {
  /* initialization */
  Expr::Ptr init = nd->init();
  process_node(init);

  In::Label::Ptr repeat_label = labelNew();
  In::Label::Ptr end_label = labelNew();

  process_instruction(repeat_label);

  /* evaluating test expression */
  Expr::Ptr test = nd->test();
  process_node(test);

  /* for test logic */
  Location::Ptr test_loc = test->location();
  process_location(test_loc);

  In::IfZ::Ptr ifz_i = In::IfZ::IfZNew(test_loc, end_label);
  process_instruction(ifz_i);

  /* for stmt_block */
  Stmt::Ptr body = nd->body();
  process_node(body);

  Expr::Ptr step = nd->step();
  process_node(step);

  /* return to beginning of for loop */
  In::Goto::Ptr goto_i = In::Goto::GotoNew(repeat_label);
  process_instruction(goto_i);

  /* end label */
  process_instruction(end_label);
}

void
CodeGenerator::NodeFunctor::operator()(WhileStmt *nd) {
  In::Label::Ptr repeat_label = labelNew();
  In::Label::Ptr end_label = labelNew();

  process_instruction(repeat_label);

  /* evaluating test expression */
  Expr::Ptr test = nd->test();
  process_node(test);

  /* while test logic */
  Location::Ptr test_loc = test->location();
  process_location(test_loc);

  In::IfZ::Ptr ifz_i = In::IfZ::IfZNew(test_loc, end_label);
  process_instruction(ifz_i);

  /* while stmt_block */
  Stmt::Ptr body = nd->body();
  process_node(body);

  /* return to beginning of while loop */
  In::Goto::Ptr goto_i = In::Goto::GotoNew(repeat_label);
  process_instruction(goto_i);

  /* end label */
  process_instruction(end_label);
}


/* stmt/expr */
void
CodeGenerator::NodeFunctor::operator()(AssignExpr *nd) {
  LValueExpr::Ptr l_val = nd->left();
  process_node(l_val);

  Operator::Ptr op = nd->op();
  process_node(op);

  Expr::Ptr rhs = nd->right();
  process_node(rhs);

  Location::Ptr lhs_loc = l_val->location();
  Location::Ptr rhs_loc = rhs->location();

  if (lhs_loc->reference()) {
    In::Store::Ptr store_i = In::Store::StoreNew(rhs_loc, lhs_loc);
    process_instruction(store_i);
  } else {
    In::Assign::Ptr assign_i = In::Assign::AssignNew(rhs_loc, lhs_loc);
    process_instruction(assign_i);
  }
}


/* stmt/expr/l_value */

void
CodeGenerator::NodeFunctor::operator()(VarAccessExpr *nd) {
  Identifier::Ptr id = nd->identifier();
  process_node(id);

  VarDecl::PtrConst var_decl = nd->varDecl();
  if (var_decl->scope()->isObjectScope()) {
    ThisExpr::Ptr base = ThisExpr::ThisExprNew(nd->parent(), nd->scope());
    process_access_expr(nd, id, base);

  } else {
    Identifier::Ptr id = nd->identifier();
    process_node(id);
  }
}

void
CodeGenerator::NodeFunctor::operator()(FieldAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Identifier::Ptr id = nd->identifier();
  process_node(id);

  process_access_expr(nd, id, base);
}

void
CodeGenerator::NodeFunctor::operator()(ArrayAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Expr::Ptr subscript = nd->subscript();
  process_node(subscript);

  size_t elem_size = MIPSEmitFunctor::kWordSize;
  // todo: remove hardware dependency (requires changing library)

  /* load elem size into aux_loc */
  In::LoadIntConst::Ptr load_int_i;
  Location::Ptr aux_loc = nd->auxLocation();
  load_int_i = In::LoadIntConst::LoadIntConstNew(aux_loc, (int)elem_size);
  process_instruction(load_int_i);

  /* multiply elem size by number of elements */
  Location::Ptr sub_loc = subscript->location();
  process_location(sub_loc);

  /* computing offset */
  In::BinaryOp::Ptr binary_op_i;
  binary_op_i = In::BinaryOp::BinaryOpNew(In::BinaryOp::kMultiply,
                                          aux_loc, aux_loc, sub_loc);
  process_instruction(binary_op_i);

  /* computing base of array */
  Location::Ptr base_loc = nd->base()->location();
  process_location(base_loc);

  /* adding offset to base of array */
  binary_op_i = In::BinaryOp::BinaryOpNew(In::BinaryOp::kAdd,
                                          aux_loc, base_loc, aux_loc);
  process_instruction(binary_op_i);

  aux_loc->referenceIs(true);
  nd->locationIs(aux_loc);
}

/* stmt/expr/single_addr */
void
CodeGenerator::NodeFunctor::operator()(BoolConstExpr *nd) {
  Location::Ptr bool_loc = nd->location();
  int value = nd->value() ? 1 : 0;

  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(bool_loc, value);

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(IntConstExpr *nd) {
  Location::Ptr int_loc = nd->location();
  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(int_loc, nd->value());

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(StrConstExpr *nd) {
  Location::Ptr str_loc = nd->location();
  In::LoadStrConst::Ptr load_i;
  load_i = In::LoadStrConst::LoadStrConstNew(str_loc, nd->value());

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(NullConstExpr *nd) {
  Location::Ptr loc = nd->location();
  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(loc, 0);

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(ReadLineExpr *nd) {
  Location::Ptr ret_loc = nd->location();

  In::LCall::Ptr l_call_i;
  l_call_i = In::LCall::LCallNew(In::Label::kReadLine, ret_loc);
  process_instruction(l_call_i);
}

void
CodeGenerator::NodeFunctor::operator()(ReadIntegerExpr *nd) {
  Location::Ptr ret_loc = nd->location();

  In::LCall::Ptr l_call_i;
  l_call_i = In::LCall::LCallNew(In::Label::kReadInteger, ret_loc);
  process_instruction(l_call_i);
}

void
CodeGenerator::NodeFunctor::operator()(NewExpr *nd) {
  Location::Ptr ret_loc = nd->location();

  NamedType::PtrConst type = nd->objectType();
  size_t size = type->allocSize() + 1; /* +1 for this ptr */
  size *= MIPSEmitFunctor::kWordSize;
  // todo: remove hardware dependency (requires changing library)

  Location::Ptr aux_loc = nd->auxLocation();

  /* load size param into temporary */
  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(aux_loc, static_cast<int>(size));
  process_instruction(load_i);

  /* push size param */
  In::PushParam::Ptr push_param_i = In::PushParam::PushParamNew(aux_loc);
  process_instruction(push_param_i);

  /* call alloc */
  In::Label::PtrConst label_i = In::Label::kAlloc;
  In::LCall::Ptr l_call_i = In::LCall::LCallNew(label_i, ret_loc);
  process_instruction(l_call_i);
  process_instruction(In::PopParams::PopParamsNew(1));

  /* assign v_ptr */
  In::LoadLabel::Ptr load_label_i;
  load_label_i = In::LoadLabel::LoadLabelNew(aux_loc, type->objectLabel());
  process_instruction(load_label_i);

  In::Store::Ptr store_i = In::Store::StoreNew(aux_loc, ret_loc);
  process_instruction(store_i);
}

void
CodeGenerator::NodeFunctor::operator()(NewArrayExpr *nd) {
  Expr::Ptr size = nd->size();
  process_node(size);

  ArrayType::Ptr type = nd->arrayType();
  process_node(type);


  size_t elem_size = MIPSEmitFunctor::kWordSize;
  // todo: remove hardware dependency (requires changing library)

  /* load elem size into aux_loc */
  In::LoadIntConst::Ptr load_int_i;
  Location::Ptr aux_loc = nd->auxLocation();
  load_int_i = In::LoadIntConst::LoadIntConstNew(aux_loc, (int)elem_size);
  process_instruction(load_int_i);

  /* size location */
  Location::Ptr size_loc = size->location();
  process_location(size_loc);

  /* multiply elem size by number of elements */
  In::BinaryOp::Ptr binary_op_i;
  binary_op_i = In::BinaryOp::BinaryOpNew(In::BinaryOp::kMultiply,
                                          aux_loc, aux_loc, size_loc);
  process_instruction(binary_op_i);

  /* PushParam */
  In::PushParam::Ptr push_param_i = In::PushParam::PushParamNew(aux_loc);
  process_instruction(push_param_i);

  /* call alloc */
  Location::Ptr ret_loc = nd->location();
  In::Label::PtrConst label_i = In::Label::kAlloc;
  In::LCall::Ptr l_call_i = In::LCall::LCallNew(label_i, ret_loc);
  process_instruction(l_call_i);
  process_instruction(In::PopParams::PopParamsNew(1));
}


/* stmt/expr/single_addr/call_expr */
void
CodeGenerator::NodeFunctor::operator()(CallExpr *nd) {
  Identifier::Ptr fn_id = nd->identifier();
  process_node(fn_id);

  Expr::Ptr actual;
  Location::Ptr actual_loc;
  In::PushParam::Ptr push_param_i;
  FunctionCallExpr::const_reverse_actuals_iter it = nd->actualsReverseBegin();
  for (; it != nd->actualsReverseEnd(); ++it) {
    actual = *it;
    process_node(actual);

    actual_loc = actual->location();
    process_location(actual_loc);

    push_param_i = In::PushParam::PushParamNew(actual_loc);
    process_instruction(push_param_i);
  }
}

void
CodeGenerator::NodeFunctor::operator()(FunctionCallExpr *nd) {
  FnDecl::PtrConst fn_decl = nd->fnDecl();
  if (fn_decl->nearestClass() != NULL) {
    MethodCallExpr::Ptr m_call = MethodCallExpr::MethodCallExprNew(nd);

    Functor::Ptr this_functor = this;
    this_functor(m_call);

  } else {
    /* applying this functor on upcasted nd */
    (*this)(static_cast<CallExpr*>(nd));

    Location::Ptr ret_loc = nd->location();
    Identifier::Ptr fn_id = nd->identifier();
    In::Label::Ptr label_i = In::Label::LabelNew(fn_id);
    In::LCall::Ptr l_call_i = In::LCall::LCallNew(label_i, ret_loc);
    process_instruction(l_call_i);

    /* PopParams */
    uint32_t words = nd->actualsCount();
    In::PopParams::Ptr pop_params_i = In::PopParams::PopParamsNew(words);
    process_instruction(pop_params_i);
  }
}

void
CodeGenerator::NodeFunctor::operator()(MethodCallExpr *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<CallExpr*>(nd));

  Expr::Ptr base = nd->base();
  process_node(base);

  /* pushing "this" pointer onto the stack */
  Location::Ptr base_loc = base->location();
  process_location(base_loc);

  In::PushParam::Ptr push_param_i = In::PushParam::PushParamNew(base_loc);
  process_instruction(push_param_i);

  /* return location */
  Location::Ptr ret_loc = nd->location();

  /* obtaining function's location */
  Location::Ptr v_ptr_loc = nd->auxLocation();
  In::Load::Ptr load_i = In::Load::LoadNew(base_loc, v_ptr_loc);
  process_instruction(load_i);

  /* offset from bottom of vtable */
  Location::Ptr method_loc = Location::LocationNew(v_ptr_loc); /* copy */
  v_ptr_loc->secondaryOffsetIs(nd->vTableOffset());

  /* dereferencing to obtain function address in v_table */
  load_i = In::Load::LoadNew(v_ptr_loc, method_loc);
  process_instruction(load_i);

    /* making l_call */
  In::ACall::Ptr a_call_i = In::ACall::ACallNew(method_loc, ret_loc);
  process_instruction(a_call_i);

  /* PopParams */
  uint32_t words = nd->actualsCount() + 1; /* +1 because of this ptr */
  In::PopParams::Ptr pop_params_i = In::PopParams::PopParamsNew(words);
  process_instruction(pop_params_i);
}


/* stmt/expr/single_addr/compound */
void
CodeGenerator::NodeFunctor::operator()(CompoundExpr *nd) {
  Expr::Ptr left = nd->left();
  process_node(left);

  Operator::Ptr op = nd->op();
  process_node(op);

  Expr::Ptr right = nd->right();
  process_node(right);
}

void
CodeGenerator::NodeFunctor::operator()(ArithmeticExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));

  Operator::OpCode op_type = nd->op()->operatorType();
  In::BinaryOp::OpCode op_code;
  switch (op_type) {
    case Operator::kAdd:
      op_code = In::BinaryOp::kAdd;
      break;

    case Operator::kSubtract:
      op_code = In::BinaryOp::kSubtract;
      break;

    case Operator::kMultiply:
      op_code = In::BinaryOp::kMultiply;
      break;

    case Operator::kDivide:
      op_code = In::BinaryOp::kDivide;
      break;

    case Operator::kModulo:
      op_code = In::BinaryOp::kModulo;
      break;

    default:
      ABORT();
  }

  Location::Ptr dst_loc = nd->location();
  Location::Ptr lhs_loc = nd->left()->location();
  Location::Ptr rhs_loc = nd->right()->location();

  process_location(lhs_loc);
  process_location(rhs_loc);

  In::BinaryOp::Ptr binary_op_i;
  binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, lhs_loc, rhs_loc);
  process_instruction(binary_op_i);
}

void
CodeGenerator::NodeFunctor::operator()(LogicalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));

  Expr::Ptr left = nd->left();
  Expr::Ptr right = nd->right();
  Operator::Ptr op = nd->op();

  bool unary = false;
  Operator::OpCode op_type = op->operatorType();
  In::BinaryOp::OpCode op_code;
  switch (op_type) {
    case Operator::kAnd:
      op_code = In::BinaryOp::kAnd;
      break;

    case Operator::kOr:
      op_code = In::BinaryOp::kOr;
      break;

    case Operator::kNot:
      unary = true;
      break;

    default:
      ABORT();
  }

  Location::Ptr dst_loc = nd->location();
  Location::Ptr rhs_loc = right->location();
  process_location(rhs_loc);

  if (not unary) {
    Location::Ptr lhs_loc = left->location();
    process_location(lhs_loc);

    In::BinaryOp::Ptr binary_op_i;
    binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, lhs_loc, rhs_loc);
    process_instruction(binary_op_i);

  } else {
    assert(left == NULL);
    Location::Ptr aux_loc = nd->auxLocation();
    negate_logical_value(dst_loc, rhs_loc, aux_loc);
  }
}

void
CodeGenerator::NodeFunctor::operator()(RelationalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));

  Location::Ptr dst_loc = nd->location();
  Location::Ptr lhs_loc = nd->left()->location();
  Location::Ptr rhs_loc = nd->right()->location();

  process_location(lhs_loc);
  process_location(rhs_loc);

  bool negate = false;
  Operator::OpCode op_type = nd->op()->operatorType();
  In::BinaryOp::OpCode op_code;
  switch (op_type) {
    case Operator::kNotEqual: negate = true; /* allow fall through */
    case Operator::kEqual:
      op_code = In::BinaryOp::kEqual;
      break;

    case Operator::kGreaterEqual: negate = true; /* allow fall through */
    case Operator::kLess:
      op_code = In::BinaryOp::kLess;
      break;

    case Operator::kLessEqual: negate = true; /* allow fall through */
    case Operator::kGreater:
      {
        op_code = In::BinaryOp::kLess;

        /* swap */
        Location::Ptr tmp_loc = lhs_loc;
        lhs_loc = rhs_loc;
        rhs_loc = tmp_loc;
      }
      break;

    default:
      ABORT();
  }

  In::BinaryOp::Ptr binary_op_i;
  binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, lhs_loc, rhs_loc);
  process_instruction(binary_op_i);

  if (negate) {
    Location::Ptr rhs_loc = nd->auxLocation();
    negate_logical_value(dst_loc, dst_loc, rhs_loc);
  }
}



/* type */
void
CodeGenerator::NodeFunctor::operator()(NamedType *nd) {
  Identifier::Ptr type_id = nd->identifier();
  process_node(type_id);
}

void
CodeGenerator::NodeFunctor::operator()(ArrayType *nd) {
  Type::Ptr type = nd->elemType();
  process_node(type);
}

/* CodeGenerator private member functions */

void
CodeGenerator::NodeFunctor::process_node(Node::Ptr _node) {
  if (_node) {
    NodeFunctor::Ptr this_functor = this;
    this_functor(_node);
  }
}

void
CodeGenerator::NodeFunctor::process_location(Location::Ptr _loc) {
  if (_loc->reference()) {
    In::Load::Ptr load_i = In::Load::LoadNew(_loc, _loc);
    process_instruction(load_i);
  }
}

void
CodeGenerator::NodeFunctor::process_instruction(In::Instruction::Ptr _in) {
  in_stream_.pushBack(_in);
}

In::Label::Ptr
CodeGenerator::NodeFunctor::labelNew() {
  stringstream label_num_out;
  label_num_out << label_num_;

  string name = "_L" + label_num_out.str();
  In::Label::Ptr label = In::Label::LabelNew(name);
  label_num_++;

  return label;
}

void
CodeGenerator::NodeFunctor::
process_access_expr(LValueExpr::Ptr _ex, Identifier::Ptr _id, Expr::Ptr _base) {
  /* obtaining field offset */
  VarDecl::PtrConst var_decl = _ex->varDecl();
  Location::Ptr var_decl_loc = var_decl->location();
  Location::Offset var_decl_off = var_decl_loc->offset() + 1; /* +1 this ptr */

  /* loading field offset into aux_loc */
  Location::Ptr aux_loc = _ex->auxLocation();
  Location::Ptr base_loc = _base->location();
  process_location(base_loc);

  In::Assign::Ptr assign_i = In::Assign::AssignNew(base_loc, aux_loc);
  process_instruction(assign_i);

  aux_loc->referenceIs(true);
  aux_loc->secondaryOffsetIs(var_decl_off);
  _ex->locationIs(aux_loc);
}

void
CodeGenerator::NodeFunctor::negate_logical_value(Location::Ptr dst_loc,
                                                 Location::Ptr rhs_loc,
                                                 Location::Ptr aux) {
  In::LoadIntConst::Ptr l_i = In::LoadIntConst::LoadIntConstNew(aux, 1);
  process_instruction(l_i);

  In::BinaryOp::Ptr binary_op_i;
  In::BinaryOp::OpCode op_code = In::BinaryOp::kAdd;
  binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, rhs_loc, aux);
  process_instruction(binary_op_i);

  l_i = In::LoadIntConst::LoadIntConstNew(aux, 2);
  process_instruction(l_i);

  op_code = In::BinaryOp::kModulo;
  binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, dst_loc, aux);
  process_instruction(binary_op_i);
}

void
CodeGenerator::emit_instruction_stream() {
  if (IsDebugOn("tac")) {
    code_emit_functor_ = TACEmitFunctor::TACEmitFunctorNew();
  } else {
    code_emit_functor_ = MIPSEmitFunctor::MIPSEmitFunctorNew();
  }

  NodeFunctor::const_instruction_iter it = node_functor_->beginIn();
  for(; it != node_functor_->endIn(); ++it) {
    In::Instruction::Ptr in = *it;
    code_emit_functor_(in);
  }
}
