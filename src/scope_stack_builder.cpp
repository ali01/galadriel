#include "scope_stack_builder.h"

#include "scope.h"

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

    /* propagate scope object down the parse tree */
    decl->scopeIs(scope);

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
  parent_scope->declIs(nd);

  /* FnDecl's parameter level scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->scopeIs(scope);
    decl->apply(this);
  }

  StmtBlock::Ptr stmt_block = nd->body();

  /* stmt_block could be NULL in the case of a function prototype */
  if (stmt_block != NULL) {
    stmt_block->scopeIs(scope); /* unnecessary but here for consistency */
    stmt_block->apply(this);
  }

  Type::Ptr return_type = nd->returnType();
  return_type->scopeIs(scope);
  return_type->apply(this);

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(ClassDecl *nd) {
  /* Class's context scope (i.e. global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();
  parent_scope->declIs(nd);

  /* Class's own scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  Decl::Ptr decl;
  ClassDecl::const_member_iter member_it = nd->membersBegin();
  for (; member_it != nd->membersEnd(); ++member_it) {
    decl = *member_it;
    decl->scopeIs(scope);
    decl->apply(this);
  }

  /* initializing scope in base class Type object */
  NamedType::Ptr base = nd->baseClass();
  if (base != NULL) {
    base->scopeIs(scope);
    base->apply(this);
  }

  /* initializing scope in interface Type objects */
  ClassDecl::const_intf_iter intf_it = nd->interfacesBegin();
  for (; intf_it != nd->interfacesEnd(); ++intf_it) {
    base = *intf_it;
    base->scopeIs(scope);
    base->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(InterfaceDecl *nd) {
  /* Interface's context scope (i.e. global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();
  parent_scope->declIs(nd);

  /* Interface's own scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  FnDecl::Ptr fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    fn_decl->scopeIs(scope); /* unnecessary but here for consistency */
    fn_decl->apply(this);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(VarDecl *nd) {
  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);
  
  /* initializing scope in type object */
  Type::Ptr type = nd->type();
  type->scopeIs(scope);
  type->apply(this);
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
    var_decl->scopeIs(scope);
    var_decl->apply(this);
  }

  Stmt::Ptr stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    stmt->scopeIs(scope);
    stmt->apply(this);
  }

  scope_stack_->scopePop();
}


/* stmt/conditional */

void
ScopeStackBuilder::NodeFunctor::operator()(ConditionalStmt *nd) {
  Scope::Ptr scope = nd->scope();

  Stmt::Ptr body = nd->body();
  body->scopeIs(scope);
  body->apply(this);

  Expr::Ptr test = nd->test();
  test->scopeIs(scope);
  test->apply(this);
}

void
ScopeStackBuilder::NodeFunctor::operator()(IfStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);

  Scope::Ptr scope = nd->scope();
  Stmt::Ptr else_body = nd->elseBody();
  if (else_body != NULL) {
    else_body->scopeIs(scope);
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


/* type */
void
ScopeStackBuilder::NodeFunctor::operator()(ArrayType *nd) {
  Scope::Ptr scope = nd->scope();
  Type::Ptr elem_type = nd->elemType();
  elem_type->scopeIs(scope);
  elem_type->apply(this);
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
