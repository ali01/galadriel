#include "scope_stack_builder.h"

ScopeStackBuilder::ScopeStackBuilder(Program::Ptr _program) {
  scope_stack_ = ScopeStack::ScopeStackNew();

  node_functor_ = NodeFunctor::NodeFunctorNew(scope_stack_);
  _program->apply(node_functor_);
}

void
ScopeStackBuilder::NodeFunctor::operator()(const Program *nd) {
  Decl::PtrConst decl;
  Program::const_decl_iter it = nd->declsBegin();

  for (; it != nd->declsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }
}



/* -- decl -- */

void
ScopeStackBuilder::NodeFunctor::operator()(const FnDecl *nd) {
  VarDecl::PtrConst decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();

  scope_stack_->scopeNew();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  StmtBlock::Ptr stmt_block = nd->body();
  if (stmt_block != NULL) {
    /* stmt_block could be NULL in the case of a function prototype */
    stmt_block->apply(this);
  }
}

void
ScopeStackBuilder::NodeFunctor::operator()(const VarDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);
}


/* decl/object */
void
ScopeStackBuilder::NodeFunctor::operator()(const ClassDecl *nd) {
  scope_stack_->scopeNew();

  Decl::PtrConst decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }
}

void
ScopeStackBuilder::NodeFunctor::operator()(const InterfaceDecl *nd) {
  scope_stack_->scopeNew();

  FnDecl::PtrConst fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    fn_decl->apply(this);
  }
}



/* -- stmt -- */

void
ScopeStackBuilder::NodeFunctor::operator()(const StmtBlock *nd) {
  scope_stack_->scopeNew();

  VarDecl::PtrConst var_decl;
  StmtBlock::const_decl_iter decl_it = nd->declsBegin();
  for (; decl_it != nd->declsEnd(); ++decl_it) {
    var_decl = *decl_it;
    var_decl->apply(this);
  }

  Stmt::PtrConst stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    stmt->apply(this);
  }
}


/* stmt/conditional */
void
ScopeStackBuilder::NodeFunctor::operator()(const IfStmt *nd) {
  Stmt::PtrConst body = nd->body();
  body->apply(this);

  Stmt::PtrConst else_body = nd->elseBody();
  if (else_body != NULL)
    else_body->apply(this);
}


/* stmt/conditional/loop */
void
ScopeStackBuilder::NodeFunctor::operator()(const ForStmt *nd) {
  Stmt::PtrConst body = nd->body();
  body->apply(this);
}

void
ScopeStackBuilder::NodeFunctor::operator()(const WhileStmt *nd) {
  Stmt::PtrConst body = nd->body();
  body->apply(this);
}


/* stmt/switch */
void
ScopeStackBuilder::NodeFunctor::operator()(const SwitchStmt *nd) {
  SwitchCaseStmt::PtrConst case_stmt;
  SwitchStmt::const_case_iter it = nd->casesBegin();
  for (; it != nd->casesEnd(); ++it) {
    case_stmt = *it;
    case_stmt->apply(this);
  }

  SwitchCaseStmt::Ptr default_case = nd->defaultCase();
  if (default_case != NULL)
    default_case->apply(this);
}

void
ScopeStackBuilder::NodeFunctor::operator()(const SwitchCaseStmt *nd) {
  Stmt::PtrConst stmt;
  SwitchCaseStmt::const_stmt_iter it = nd->stmtsBegin();
  for (; it != nd->stmtsEnd(); ++it) {
    stmt = *it;
    stmt->apply(this);
  }
}
