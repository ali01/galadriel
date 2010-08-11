#include "code_generator.h"

/* project includes */
#include <ast_includes.h>
#include <utility.h> // TODO

/* local includes */
#include "instruction_includes.h"
#include "location.h"
#include "mips_emit_functor.h"
#include "tac_emit_functor.h"

CodeGenerator::CodeGenerator(Simone::Ptr<Program> _prog) {
  node_functor_ = NodeFunctor::NodeFunctorNew();
  node_functor_(_prog);
}

CodeGenerator::NodeFunctor::NodeFunctor() {
  if (IsDebugOn("tac")) {
    code_emit_functor_ = TACEmitFunctor::TACEmitFunctorNew();
  } else {
    code_emit_functor_ = MIPSEmitFunctor::MIPSEmitFunctorNew();
  }
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
  Identifier::Ptr fn_id = nd->identifier();
  Label::Ptr label_i = Label::LabelNew(fn_id); // TODO: think about identifier
  BeginFunc::Ptr begin_func_i  = BeginFunc::BeginFuncNew(label_i, 0); // TODO: 0

  code_emit_functor_(begin_func_i);

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
  process_node(stmt_block);
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
  /* apply this functor to upcasted nd */
  (*this)(static_cast<ObjectDecl*>(nd));
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
  PrintStmt::const_arg_iterator it = nd->argsBegin();
  for (int i = 1; it != nd->argsEnd(); ++it, ++i) {
    arg = *it;
    process_node(arg);
  }
}

void
CodeGenerator::NodeFunctor::operator()(ReturnStmt *nd) {
  Expr::Ptr expr = nd->expr();
  process_node(expr);
}

void
CodeGenerator::NodeFunctor::operator()(BreakStmt *nd) {
  
}


/* stmt/conditional */
void
CodeGenerator::NodeFunctor::operator()(ConditionalStmt *nd) {
  Expr::Ptr test = nd->test();
  process_node(test);

  Stmt::Ptr body = nd->body();
  process_node(body);
}

void
CodeGenerator::NodeFunctor::operator()(IfStmt *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));

  Stmt::Ptr else_body = nd->elseBody();
  process_node(else_body);
}


/* stmt/conditional/loop */
void
CodeGenerator::NodeFunctor::operator()(ForStmt *nd) {
  Expr::Ptr init = nd->init();
  process_node(init);

  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));

  Expr::Ptr step = nd->step();
  process_node(step);
}

void
CodeGenerator::NodeFunctor::operator()(WhileStmt *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));
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
}


/* stmt/expr/call_expr */
void
CodeGenerator::NodeFunctor::operator()(CallExpr *nd) {
  Identifier::Ptr fn_id = nd->identifier();
  process_node(fn_id);

  Expr::Ptr actual;
  FunctionCallExpr::const_actuals_iter it = nd->actualsBegin();
  for (; it != nd->actualsEnd(); ++it) {
    actual = *it;
    process_node(actual);
  }
}

void
CodeGenerator::NodeFunctor::operator()(FunctionCallExpr *nd) {
  Identifier::Ptr fn_id = nd->identifier();
  Label::Ptr label_i = Label::LabelNew(fn_id);
  LCall::Ptr l_call_i = LCall::LCallNew(label_i, NULL); // TODO: resolve NULL

  code_emit_functor_(l_call_i);

  /* applying this functor on upcasted nd */
  (*this)(static_cast<CallExpr*>(nd));
}

void
CodeGenerator::NodeFunctor::operator()(MethodCallExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  /* applying this functor on upcasted nd */
  (*this)(static_cast<CallExpr*>(nd));
}


/* stmt/expr/single_addr */
void
CodeGenerator::NodeFunctor::operator()(IntConstExpr *nd) {
  // TODO: resolve NULL
  LoadIntConst::Ptr load_i;
  load_i = LoadIntConst::LoadIntConstNew(NULL, nd->value());
  code_emit_functor_(load_i);
}

void
CodeGenerator::NodeFunctor::operator()(NewExpr *nd) {
  
}

void
CodeGenerator::NodeFunctor::operator()(NewArrayExpr *nd) {
  Expr::Ptr size = nd->size();
  process_node(size);

  ArrayType::Ptr type = nd->arrayType();
  process_node(type);
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
}

void
CodeGenerator::NodeFunctor::operator()(LogicalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}

void
CodeGenerator::NodeFunctor::operator()(RelationalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}


/* stmt/expr/single_addr/l_value */
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
