#include "semantic_analyser.h"

/* project includes */
#include <ast.h>
#include <error.h>
#include <scope_stack_builder.h>

SemanticAnalyser::SemanticAnalyser(Program::Ptr _prog) {
  sm_builder_ = ScopeStackBuilder::ScopeStackBuilderNew(_prog);
  node_functor_ = NodeFunctor::NodeFunctorNew();
  _prog->apply(node_functor_);
}

void
SemanticAnalyser::NodeFunctor::operator()(Program *nd) {
  Decl::Ptr decl;
  Program::const_decl_iter it = nd->declsBegin();
  for (; it != nd->declsEnd(); ++it) {
    decl = *it;
    process_node(decl);
  }
}



/* -- decl -- */

void
SemanticAnalyser::NodeFunctor::operator()(Decl *nd) {
  Identifier::Ptr id = nd->identifier();
  process_node(id);
}

void
SemanticAnalyser::NodeFunctor::operator()(VarDecl *nd) {
  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  Type::Ptr type = nd->type();
  process_node(type);
}

void
SemanticAnalyser::NodeFunctor::operator()(FnDecl *nd) {
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

void
SemanticAnalyser::NodeFunctor::operator()(ClassDecl *nd) {
  if (nd->indexed())
    return;

  nd->indexedIs(true);

  /* apply this functor to upcasted nd */
  (*this)(static_cast<Decl*>(nd));

  inherit_base_class_scopes(nd);
  inherit_interface_scopes(nd);

  Decl::Ptr decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    process_node(decl);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(InterfaceDecl *nd) {
  FnDecl::Ptr fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    process_node(fn_decl);
  }
}

/* -- stmt -- */

void
SemanticAnalyser::NodeFunctor::operator()(StmtBlock *nd) {
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
SemanticAnalyser::NodeFunctor::operator()(PrintStmt *nd) {
  Expr::Ptr arg;
  PrintStmt::const_arg_iterator it = nd->argsBegin();
  for (; it != nd->argsEnd(); ++it) {
    arg = *it;
    process_node(arg);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(ReturnStmt *nd) {
  Expr::Ptr expr = nd->expr();
  process_node(expr);
}

/* stmt/conditional */

void
SemanticAnalyser::NodeFunctor::operator()(ConditionalStmt *nd) {
  Expr::Ptr test = nd->test();
  process_node(test);

  Stmt::Ptr body = nd->body();
  process_node(body);
}

void
SemanticAnalyser::NodeFunctor::operator()(IfStmt *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));

  Stmt::Ptr else_body = nd->elseBody();
  process_node(else_body);
}


/* stmt/conditional/loop */
void
SemanticAnalyser::NodeFunctor::operator()(ForStmt *nd) {
  Expr::Ptr init = nd->init();
  process_node(init);

  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));

  Expr::Ptr step = nd->step();
  process_node(step);
}

void
SemanticAnalyser::NodeFunctor::operator()(WhileStmt *nd) {
  /* applying this functor on upcasted nd */
  (*this)(static_cast<ConditionalStmt*>(nd));
}


/* stmt/expr */
void
SemanticAnalyser::NodeFunctor::operator()(AssignExpr *nd) {
  LValueExpr::Ptr l_val = nd->left();
  process_node(l_val);

  Operator::Ptr op = nd->op();
  process_node(op);

  Expr::Ptr rhs = nd->right();
  process_node(rhs);

  Type::PtrConst l_val_type = l_val->type();
  Type::PtrConst rhs_type = rhs->type();

  if (not l_val_type->subsumes(rhs_type)) {
    Error::IncompatibleOperands(op, l_val_type, rhs_type);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(CallExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Identifier::Ptr function = nd->function();
  process_node(function);

  /* obtaining function declaration */
  FnDecl::PtrConst fn_decl = nd->fnDecl();
  if (fn_decl == NULL) {
    Error::IdentifierNotDeclared(function, kLookingForFunction);
  }

  Expr::Ptr actual;
  CallExpr::const_actuals_iter it = nd->actualsBegin();
  for(; it != nd->actualsEnd(); ++it) {
    actual = *it;
    process_node(actual);
  }
}


/* stmt/expr/single_addr */
void
SemanticAnalyser::NodeFunctor::operator()(NewExpr *nd) {
  NamedType::Ptr type = nd->objectType();
  ClassDecl::Ptr class_decl = type->classDecl();
  if (class_decl) {
    process_node(class_decl);
  } else {
    Error::IdentifierNotDeclared(type->identifier(), kLookingForClass);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(NewArrayExpr *nd) {
  Expr::Ptr size = nd->size();
  process_node(size);

  ArrayType::Ptr type = nd->arrayType();
  process_node(type);

  // TODO
  // Type::Ptr type = nd->elemType();
  //   process_node(type);
}


/* stmt/expr/single_addr/compound */
void
SemanticAnalyser::NodeFunctor::operator()(CompoundExpr *nd) {
  Expr::Ptr left = nd->left();
  process_node(left);

  Operator::Ptr op = nd->op();
  process_node(op);

  Expr::Ptr right = nd->right();
  process_node(right);

  /* right must be non-null */
  Type::PtrConst right_type = right->type();

  if (left) {
    Type::PtrConst left_type = left->type();

    if (*left_type != *right_type)
      Error::IncompatibleOperands(op, left_type, right_type);

  } else {
    bool error = false;

    if (op->operatorType() == Operator::kSubtract) {
      if (right_type != Type::kInt && right_type != Type::kDouble){
        error = true;
      }
    } else if (op->operatorType() == Operator::kNot) {
      if (right_type != Type::kBool) {
        error = true;
      }
    }

    if (error)
      Error::IncompatibleOperand(op, right_type);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(ArithmeticExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}

void
SemanticAnalyser::NodeFunctor::operator()(LogicalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}

void
SemanticAnalyser::NodeFunctor::operator()(RelationalExpr *nd) {
  (*this)(static_cast<CompoundExpr*>(nd));
}


/* stmt/expr/single_addr/l_value */
void
SemanticAnalyser::NodeFunctor::operator()(VarAccessExpr *nd) {
  Identifier::Ptr id = nd->identifier();
  process_node(id);
}

void
SemanticAnalyser::NodeFunctor::operator()(ArrayAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Expr::Ptr subscript = nd->subscript();
  process_node(subscript);
}

void
SemanticAnalyser::NodeFunctor::operator()(FieldAccessExpr *nd) {
  Expr::Ptr base = nd->base();
  process_node(base);

  Identifier::Ptr id = nd->field();
  process_node(id);
}



/* type */
void
SemanticAnalyser::NodeFunctor::operator()(NamedType *nd) {
  Scope::Ptr scope = nd->scope();
  Identifier::Ptr type_id = nd->identifier();
  process_node(type_id);

  ClassDecl::PtrConst class_decl = nd->classDecl();
  if (class_decl == NULL) {
    InterfaceDecl::Ptr intf_decl = scope->interfaceDecl(type_id);
    if (intf_decl == NULL) {
      Error::IdentifierNotDeclared(type_id, kLookingForType);
    }
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(ArrayType *nd) {
  Type::Ptr type = nd->elemType();
  process_node(type);
}


/* SemanticAnalyser private member functions */

void
SemanticAnalyser::NodeFunctor::process_node(Node::Ptr _node) {
  if (_node)
    _node->apply(this);
}

// TODO: implement in terms of NamedType function
void
SemanticAnalyser::NodeFunctor::
inherit_base_class_scopes(ClassDecl::Ptr nd, IdentifierSet::Ptr _seen) {
  NamedType::Ptr base_class_type = nd->baseClass();
  if (base_class_type != NULL) {
    /* obtain base class identifier */
    Identifier::Ptr base_id = base_class_type->identifier();

    /* search for base class decl in scope */
    Scope::Ptr scope = nd->scope();
    ClassDecl::Ptr base_decl = scope->classDecl(base_id);

    if (base_decl != NULL) {
      /* ensure that there is no cycle in the inheritance hierarchy */
      if (_seen == NULL) {
        _seen = IdentifierSet::SetNew();
      } else {
        IdentifierSet::const_iterator it = _seen->element(base_id);
        if (it != _seen->end()) {
          Error::InheritanceCycle(base_decl);
          return;
        }
      }

      _seen->elementIs(base_id);

      /* recursively process base_decl in order to inherit all ancestors */
      inherit_base_class_scopes(base_decl, _seen);

      /* inherit from base scope */
      Scope::PtrConst base_scope = base_decl->scope();
      scope->baseScopeIs(base_scope);

      /* add base scope as a subsumer */
      nd->subsumersInsert(base_class_type);

      /* inherit base scope's subsumers */
      nd->subsumersInsert(base_decl->subsumersBegin(),
                          base_decl->subsumersEnd());

    } else {
      Error::IdentifierNotDeclared(base_id, kLookingForClass);
    }
  }
}

void
SemanticAnalyser::NodeFunctor::
inherit_interface_scopes(ClassDecl::Ptr nd) {
  NamedType::Ptr intf_type;
  Identifier::Ptr base_id;
  InterfaceDecl::PtrConst intf_decl;

  Scope::Ptr scope = nd->scope();
  Scope::PtrConst intf_scope, parent_scope = scope->parentScope();

  ClassDecl::const_intf_iter it = nd->interfacesBegin();
  for (; it != nd->interfacesEnd(); ++it) {
    intf_type = *it;
    base_id = intf_type->identifier();
    intf_decl = parent_scope->interfaceDecl(base_id);

    if (intf_decl != NULL) {
      /* inherit interface scope */
      intf_scope = intf_decl->scope();
      scope->baseScopeIs(intf_scope);

      /* add interface type as a subsumer */
      nd->subsumersInsert(intf_type);

    } else {
      Error::IdentifierNotDeclared(base_id, kLookingForInterface);
    }
  }
}
