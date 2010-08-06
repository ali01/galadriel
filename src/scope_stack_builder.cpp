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

  /* inserting library built-ins */
  ClassDecl::Ptr array_class;
  array_class = ClassDecl::ClassDeclNew(ArrayType::kArrayClassIdentifier);
  
  FnDecl::Ptr length_fn;
  length_fn = FnDecl::FnDeclNew(ArrayType::kLengthFnIdentifier, Type::kInt);
  array_class->memberInsert(length_fn);

  nd->declInsert(array_class);

  Decl::Ptr decl;
  Program::const_decl_iter it = nd->declsBegin();
  for (; it != nd->declsEnd(); ++it) {
    decl = *it;
    init_node_scope(decl, nd, scope);
  }

  scope_stack_->scopePop();
}



/* -- decl -- */

void
ScopeStackBuilder::NodeFunctor::operator()(Decl *nd) {
  Scope::Ptr scope = nd->scope();
  Identifier::Ptr id = nd->identifier();
  init_node_scope(id, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(VarDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  Scope::Ptr scope = scope_stack_->scope();
  scope->declIs(nd);
  
  /* initializing scope in type object */
  Type::Ptr type = nd->type();
  init_node_scope(type, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(FnDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

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
    init_node_scope(decl, nd, scope);
  }

  StmtBlock::Ptr stmt_block = nd->body();
  init_node_scope(stmt_block, nd, scope);

  Type::Ptr return_type = nd->returnType();
  init_node_scope(return_type, nd, scope);

  scope_stack_->scopePop();
}


void
ScopeStackBuilder::NodeFunctor::operator()(ObjectDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  /* Object's context scope (i.e. global scope) */
  Scope::Ptr parent_scope = scope_stack_->scope();
  parent_scope->declIs(nd);

  /* Object's own scope (independent copy) */
  Scope::Ptr scope = scope_stack_->scopeNew();
  nd->scopeIs(scope);

  Decl::Ptr decl;
  ClassDecl::const_member_iter member_it = nd->membersBegin();
  for (; member_it != nd->membersEnd(); ++member_it) {
    decl = *member_it;
    init_node_scope(decl, nd, scope);
  }

  scope_stack_->scopePop();
}

// TODO: ordering
void
ScopeStackBuilder::NodeFunctor::operator()(ClassDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<ObjectDecl*>(nd));

  Scope::Ptr scope = nd->scope();

  /* initializing scope in base class Type object */
  NamedType::Ptr base = nd->baseClass();
  init_node_scope(base, nd, scope);

  /* initializing scope in interface Type objects */
  ClassDecl::const_intf_iter intf_it = nd->interfacesBegin();
  for (; intf_it != nd->interfacesEnd(); ++intf_it) {
    base = *intf_it;
    init_node_scope(base, nd, scope);
  }
}

void
ScopeStackBuilder::NodeFunctor::operator()(InterfaceDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<ObjectDecl*>(nd));
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
    init_node_scope(var_decl, nd, scope);
  }

  Stmt::Ptr stmt;
  StmtBlock::const_stmt_iter stmt_it = nd->stmtsBegin();
  for (; stmt_it != nd->stmtsEnd(); ++stmt_it) {
    stmt = *stmt_it;
    init_node_scope(stmt, nd, scope);
  }

  scope_stack_->scopePop();
}

void
ScopeStackBuilder::NodeFunctor::operator()(PrintStmt *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr arg;
  PrintStmt::const_arg_iterator it = nd->argsBegin();
  for (; it != nd->argsEnd(); ++it) {
    arg = *it;
    init_node_scope(arg, nd, scope);
  }
}

void
ScopeStackBuilder::NodeFunctor::operator()(ReturnStmt *nd) {
  Scope::Ptr scope = nd->scope();
  
  Expr::Ptr expr = nd->expr();
  init_node_scope(expr, nd, scope);
}

/* stmt/conditional */

void
ScopeStackBuilder::NodeFunctor::operator()(ConditionalStmt *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr test = nd->test();
  init_node_scope(test, nd, scope);

  Stmt::Ptr body = nd->body();
  init_node_scope(body, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(IfStmt *nd) {
  (*this)(static_cast<ConditionalStmt*>(nd));

  Scope::Ptr scope = nd->scope();
  Stmt::Ptr else_body = nd->elseBody();
  init_node_scope(else_body, nd, scope);
}


/* stmt/conditional/loop */
void
ScopeStackBuilder::NodeFunctor::operator()(ForStmt *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr init = nd->init();
  init_node_scope(init, nd, scope);

  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));

  Expr::Ptr step = nd->step();
  init_node_scope(step, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(WhileStmt *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));
}


/* stmt/expr */
void
ScopeStackBuilder::NodeFunctor::operator()(AssignExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr left = nd->left();
  init_node_scope(left, nd, scope);

  Operator::Ptr op = nd->op();
  init_node_scope(op, nd, scope);

  Expr::Ptr right = nd->right();
  init_node_scope(right, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(CallExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr base = nd->base();
  init_node_scope(base, nd, scope);

  Identifier::Ptr function = nd->function();
  init_node_scope(function, nd, scope);

  Expr::Ptr actual;
  CallExpr::const_actuals_iter it = nd->actualsBegin();
  for(; it != nd->actualsEnd(); ++it) {
    actual = *it;
    init_node_scope(actual, nd, scope);
  }
}


/* stmt/expr/single_addr */
void
ScopeStackBuilder::NodeFunctor::operator()(NewExpr *nd) {
  Scope::Ptr scope = nd->scope();

  NamedType::Ptr type = nd->objectType();
  init_node_scope(type, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(NewArrayExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr size = nd->size();
  init_node_scope(size, nd, scope);

  ArrayType::Ptr type = nd->arrayType();
  init_node_scope(type, nd, scope);
}


/* stmt/expr/single_addr/compound */
void
ScopeStackBuilder::NodeFunctor::operator()(CompoundExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr left = nd->left();
  init_node_scope(left, nd, scope);

  Operator::Ptr op = nd->op();
  init_node_scope(op, nd, scope);

  Expr::Ptr right = nd->right();
  init_node_scope(right, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(ArithmeticExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}

void
ScopeStackBuilder::NodeFunctor::operator()(LogicalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}

void
ScopeStackBuilder::NodeFunctor::operator()(RelationalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}


/* stmt/expr/single_addr/l_value */

void
ScopeStackBuilder::NodeFunctor::operator()(VarAccessExpr *nd) {
  Scope::Ptr scope = nd->scope();
  Identifier::Ptr id = nd->identifier();
  init_node_scope(id, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(ArrayAccessExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr base = nd->base();
  init_node_scope(base, nd, scope);

  Expr::Ptr subscript = nd->subscript();
  init_node_scope(subscript, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(FieldAccessExpr *nd) {
  Scope::Ptr scope = nd->scope();

  Expr::Ptr base = nd->base();
  init_node_scope(base, nd, scope);

  Identifier::Ptr id = nd->field();
  init_node_scope(id, nd, scope);
}


/* type */
void
ScopeStackBuilder::NodeFunctor::operator()(NamedType *nd) {
  Scope::Ptr scope = nd->scope();
  Identifier::Ptr id = nd->identifier();
  init_node_scope(id, nd, scope);
}

void
ScopeStackBuilder::NodeFunctor::operator()(ArrayType *nd) {
  Scope::Ptr scope = nd->scope();
  Type::Ptr elem_type = nd->elemType();
  init_node_scope(elem_type, nd, scope);
}



/* private member functions */
void
ScopeStackBuilder::NodeFunctor::
init_node_scope(Node::Ptr _node, Node::Ptr _parent, Scope::Ptr _scope) {
  if (_node) {
    _node->parentIs(_parent);
  
    /* propagate scope object down the parse tree */
    _node->scopeIs(_scope);

    /* recursively apply this functor to node object */
    _node->apply(this);
  }
}
