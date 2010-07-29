#include "scope_stack_builder.h"

#include "scope.h"
#include "local_scope.h"

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

  /* Program node owns its local scope (initialized in constructor) */
  LocalScope::Ptr local_scope = nd->localScope();

  Decl::Ptr decl;
  Program::const_decl_iter it = nd->declsBegin();
  for (; it != nd->declsEnd(); ++it) {
    decl = *it;

    /* propagate scope objects down the parse tree */
    decl->scopesAre(scope, local_scope);

    /* apply this functor to each program declaration */
    decl->apply(this);
  }

  scope_stack_->scopePop();
}



/* -- decl -- */

void
ScopeStackBuilder::NodeFunctor::operator()(FnDecl *nd) {
  /* FnDecl's context scope (i.e. class, interface or global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();

  /* FnDecl's parameter level scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();

  ScopeStackBuilder::transition_into_decl_block_scope(nd, parent_scope, scope);

  /* FnDecl node owns its local scope (initialized in its constructor) */
  LocalScope::Ptr local_scope = nd->localScope();

  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->scopesAre(scope, local_scope);
    decl->apply(this);
  }

  StmtBlock::Ptr stmt_block = nd->body();

  /* stmt_block could be NULL in the case of a function prototype */
  if (stmt_block != NULL) {
    /* StmtBlock node owns it's scope objects; there's no need to propagate */
    stmt_block->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(ClassDecl *nd) {
  /* Class's context scope (i.e. global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();

  /* Class's own scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();

  ScopeStackBuilder::transition_into_decl_block_scope(nd, parent_scope, scope);

  /* ClassDecl owns its local scope (initialized in its constructor) */
  LocalScope::Ptr local_scope = nd->localScope();

  Decl::Ptr decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    decl->scopesAre(scope, local_scope);
    decl->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(InterfaceDecl *nd) {
  /* Interface's context scope (i.e. global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();

  /* Interface's own scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();

  ScopeStackBuilder::transition_into_decl_block_scope(nd, parent_scope, scope);

  /* InterfaceDecl owns its local scope (initialized in its constructor) */
  LocalScope::Ptr local_scope = nd->localScope();

  FnDecl::Ptr fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    fn_decl->apply(this);
    /* FnDecl owns it's own scope objects; there's no need to propagate */
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(VarDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  LocalScope::Ptr local_scope = nd->localScope();

  scope->declIs(nd);
  local_scope->declIs(nd);
}


/* -- stmt -- */

void
ScopeStackBuilder::NodeFunctor::operator()(StmtBlock *nd) {
  /* initialize stmt_block scope */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  /* StmtBlock owns its local scope (initialized in its constructor) */
  LocalScope::Ptr local_scope = nd->localScope();

  VarDecl::Ptr var_decl;
  StmtBlock::const_decl_iter decl_it = nd->declsBegin();
  for (; decl_it != nd->declsEnd(); ++decl_it) {
    var_decl = *decl_it;
    var_decl->scopesAre(scope, local_scope);
    var_decl->apply(this);
  }

  Stmt::Ptr stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    stmt->scopesAre(scope, local_scope);
    stmt->apply(this);
  }

  scope_stack_->scopePop();
}


/* stmt/conditional */

void
ScopeStackBuilder::NodeFunctor::operator()(ConditionalStmt *nd) {
  Scope::Ptr scope = nd->scope();
  LocalScope::Ptr local_scope = nd->localScope();

  Stmt::Ptr body = nd->body();
  body->scopesAre(scope, local_scope);
  body->apply(this);
}

void
ScopeStackBuilder::NodeFunctor::operator()(IfStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);

  Scope::Ptr scope = nd->scope();
  LocalScope::Ptr local_scope = nd->localScope();

  Stmt::Ptr else_body = nd->elseBody();
  if (else_body != NULL) {
    else_body->scopesAre(scope, local_scope);
    else_body->apply(this);
  }
}


/* stmt/conditional/loop */
void
ScopeStackBuilder::NodeFunctor::operator()(ForStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);
}

void
ScopeStackBuilder::NodeFunctor::operator()(WhileStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);
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


/* -- private functions -- */

void
ScopeStackBuilder::transition_into_decl_block_scope(Decl *decl,
                                                    Scope::Ptr parent_scope,
                                                    Scope::Ptr scope) {
  /* add declaration's identifier to parent scope */
  parent_scope->declIs(decl);

  /* Decl owns its scope;
     replace scope object with independent copy */
  decl->scopeIs(scope);
}
