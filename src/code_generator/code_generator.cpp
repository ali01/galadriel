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
    In::BeginFunc::Ptr begin_func_i = In::BeginFunc::BeginFuncNew(nd->label());
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
    v_table_i = In::VTable::VTableNew(nd->label(false), fn_labels);
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
  Location::PtrConst loc;

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
  }
}

void
CodeGenerator::NodeFunctor::operator()(ReturnStmt *nd) {
  Expr::Ptr expr = nd->expr();
  process_node(expr);

  Location::PtrConst eval_loc;
  if (expr != NULL) {
    eval_loc = expr->location();
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

  Location::PtrConst test_loc = test->location();
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
  Location::PtrConst test_loc = test->location();
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
  Location::PtrConst test_loc = test->location();
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

  Location::PtrConst lhs_loc = l_val->location();
  Location::PtrConst rhs_loc = rhs->location();

  In::Assign::Ptr assign_i = In::Assign::AssignNew(rhs_loc, lhs_loc);
  process_instruction(assign_i);
}


/* stmt/expr/l_value */
void
CodeGenerator::NodeFunctor::operator()(VarAccessExpr *nd) {
  Identifier::Ptr id = nd->identifier();
  process_node(id);
}

void
CodeGenerator::NodeFunctor::operator()(ArrayAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Expr::Ptr subscript = nd->subscript();
  process_node(subscript);
}

void
CodeGenerator::NodeFunctor::operator()(FieldAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Identifier::Ptr id = nd->field();
  process_node(id);
}

void
CodeGenerator::NodeFunctor::operator()(ThisExpr *nd) {

}


/* stmt/expr/single_addr */
void
CodeGenerator::NodeFunctor::operator()(BoolConstExpr *nd) {
  Location::PtrConst bool_loc = nd->location();
  int value = nd->value() ? 1 : 0;

  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(bool_loc, value);

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(IntConstExpr *nd) {
  Location::PtrConst int_loc = nd->location();
  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(int_loc, nd->value());

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(StrConstExpr *nd) {
  Location::PtrConst str_loc = nd->location();
  In::LoadStrConst::Ptr load_i;
  load_i = In::LoadStrConst::LoadStrConstNew(str_loc, nd->value());

  process_instruction(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(NewExpr *nd) {
  Location::PtrConst ret_loc = nd->location();

  NamedType::PtrConst type = nd->objectType();
  size_t size = type->allocSize() * MIPSEmitFunctor::kWordSize;
   // TODO: remove hardware dependency (requires changing library)

  Location::PtrConst int_loc = nd->sizeLocation();

  /* load size param into temporary */
  In::LoadIntConst::Ptr load_i;
  load_i = In::LoadIntConst::LoadIntConstNew(int_loc, static_cast<int>(size));
  process_instruction(load_i);

  /* push size param */
  In::PushParam::Ptr push_param_i = In::PushParam::PushParamNew(int_loc);
  process_instruction(push_param_i);

  /* call alloc */
  In::Label::PtrConst label_i = In::Label::kAlloc;
  In::LCall::Ptr l_call_i = In::LCall::LCallNew(label_i, ret_loc);
  process_instruction(l_call_i);

  /* assign v_ptr */
  Location::PtrConst v_ptr_loc = nd->vPtrLocation();

  In::LoadLabel::Ptr load_label_i;
  load_label_i = In::LoadLabel::LoadLabelNew(v_ptr_loc, type->objectLabel());
  process_instruction(load_label_i);

  In::Store::Ptr store_i = In::Store::StoreNew(v_ptr_loc, ret_loc);
  process_instruction(store_i);
}

void
CodeGenerator::NodeFunctor::operator()(NewArrayExpr *nd) {
  Expr::Ptr size = nd->size();
  process_node(size);

  ArrayType::Ptr type = nd->arrayType();
  process_node(type);
}


/* stmt/expr/single_addr/call_expr */
void
CodeGenerator::NodeFunctor::operator()(CallExpr *nd) {
  Identifier::Ptr fn_id = nd->identifier();
  process_node(fn_id);

  Expr::Ptr actual;
  Location::PtrConst actual_loc;
  In::PushParam::Ptr push_param_i;
  FunctionCallExpr::const_reverse_actuals_iter it = nd->actualsReverseBegin();
  for (; it != nd->actualsReverseEnd(); ++it) {
    actual = *it;
    process_node(actual);

    actual_loc = actual->location();
    push_param_i = In::PushParam::PushParamNew(actual_loc);
    process_instruction(push_param_i);
  }
}

void
CodeGenerator::NodeFunctor::operator()(FunctionCallExpr *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<CallExpr*>(nd));

  Location::PtrConst ret_loc = nd->location();
  Identifier::Ptr fn_id = nd->identifier();
  In::Label::Ptr label_i = In::Label::LabelNew(fn_id);
  In::LCall::Ptr l_call_i = In::LCall::LCallNew(label_i, ret_loc);
  process_instruction(l_call_i);
  
  // TODO: PopParams
}

void
CodeGenerator::NodeFunctor::operator()(MethodCallExpr *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<CallExpr*>(nd));

  Expr::Ptr base = nd->base();
  process_node(base);

  /* pushing "this" pointer onto the stack */
  Location::PtrConst base_loc = base->location();
  In::PushParam::Ptr push_param_i = In::PushParam::PushParamNew(base_loc);
  process_instruction(push_param_i);

  // /* obtaining function's location */
  // Location::PtrConst base_loc = base->location();
  // Location::PtrConst fn_loc = ...;
  // 
  // 
  // Location::PtrConst ret_loc = nd->location();
  // In::ACall::Ptr a_call_i = In::ACall:ACallNew(fn_loc, ret_loc);
  // process_instruction(a_call_i);

  // TODO: PopParams
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

  Location::PtrConst dst_loc = nd->location();
  Location::PtrConst lhs_loc = nd->left()->location();
  Location::PtrConst rhs_loc = nd->right()->location();

  In::BinaryOp::Ptr binary_op_i;
  binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, lhs_loc, rhs_loc);
  process_instruction(binary_op_i);
}

void
CodeGenerator::NodeFunctor::operator()(LogicalExpr *nd) { // TODO
  (*this)(static_cast<CompoundExpr*>(nd));

  // Operator::OpCode op_type = nd->op()->operatorType();
  // In::BinaryOp::OpCode op_code;
  // switch (op_type) {
  //   case Operator::kAnd:
  //     
  //   case Operator::kOr:
  //   case Operator::kNot:
  //   default:
  //     ABORT();
  // }
}

void
CodeGenerator::NodeFunctor::operator()(RelationalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));

  Location::PtrConst dst_loc = nd->location();
  Location::PtrConst lhs_loc = nd->left()->location();
  Location::PtrConst rhs_loc = nd->right()->location();

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
        Location::PtrConst tmp_loc = lhs_loc;
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
    // TODO:
    // In::BinaryOp::OpCode op_code = In::BinaryOp::kAdd;
    // 
    // In::BinaryOp::Ptr binary_op_i;
    // binary_op_i = In::BinaryOp::BinaryOpNew(op_code, dst_loc, dst_loc, rhs_loc);
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
