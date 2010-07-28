#include "scope_stack_builder.h"

ScopeStackBuilder::ScopeStackBuilder(Program::Ptr _program) {
  scope_stack_ = ScopeStack::ScopeStackNew();

  node_functor_ = NodeFunctor::NodeFunctorNew(scope_stack_);
  _program->apply(node_functor_);
}

void
ScopeStackBuilder::NodeFunctor::operator()(Program *nd) {
  /* initialize global scope */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  Decl::Ptr decl;
  Program::const_decl_iter it = nd->declsBegin();

  for (; it != nd->declsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  scope_stack_->scopePop();
}



/* -- decl -- */

void
ScopeStackBuilder::NodeFunctor::operator()(FnDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);

  /* initialize function parameter scope (reuse scope ptr) */
  scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();

  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  StmtBlock::Ptr stmt_block = nd->body();
  if (stmt_block != NULL) {
    /* stmt_block could be NULL in the case of a function prototype */
    stmt_block->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(VarDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);
}


/* decl/object */
void
ScopeStackBuilder::NodeFunctor::operator()(ClassDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);

  /* initialize class scope (reuse scope ptr) */
  scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);
  

  Decl::Ptr decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(InterfaceDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);

  /* initialize interface scope (reuse scope ptr) */
  scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  FnDecl::Ptr fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    fn_decl->apply(this);
  }

  scope_stack_->scopePop();
}



/* -- stmt -- */

void
ScopeStackBuilder::NodeFunctor::operator()(StmtBlock *nd) {
  /* initialize stmt_block scope */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  VarDecl::Ptr var_decl;
  StmtBlock::const_decl_iter decl_it = nd->declsBegin();
  for (; decl_it != nd->declsEnd(); ++decl_it) {
    var_decl = *decl_it;
    var_decl->apply(this);
  }

  Stmt::Ptr stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    stmt->apply(this);
  }

  scope_stack_->scopePop();
}


/* stmt/conditional */
void
ScopeStackBuilder::NodeFunctor::operator()(IfStmt *nd) {
  Stmt::Ptr body = nd->body();
  body->apply(this);

  Stmt::Ptr else_body = nd->elseBody();
  if (else_body != NULL)
    else_body->apply(this);
}


/* stmt/conditional/loop */
void
ScopeStackBuilder::NodeFunctor::operator()(ForStmt *nd) {
  Stmt::Ptr body = nd->body();
  body->apply(this);
}

void
ScopeStackBuilder::NodeFunctor::operator()(WhileStmt *nd) {
  Stmt::Ptr body = nd->body();
  body->apply(this);
}


/* stmt/switch */
void
ScopeStackBuilder::NodeFunctor::operator()(SwitchStmt *nd) {
  SwitchCaseStmt::Ptr case_stmt;
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
ScopeStackBuilder::NodeFunctor::operator()(SwitchCaseStmt *nd) {
  Stmt::Ptr stmt;
  SwitchCaseStmt::const_stmt_iter it = nd->stmtsBegin();
  for (; it != nd->stmtsEnd(); ++it) {
    stmt = *it;
    stmt->apply(this);
  }
}
