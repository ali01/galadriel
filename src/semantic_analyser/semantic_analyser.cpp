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

    /* apply this functor to each program declaration */
    decl->apply(this);
  }
}



/* -- decl -- */

void
SemanticAnalyser::NodeFunctor::operator()(VarDecl *nd) {
  Type::Ptr type = nd->type();
  type->apply(this);
}

void
SemanticAnalyser::NodeFunctor::operator()(FnDecl *nd) {
  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  /* stmt_block could be NULL in the case of a function prototype */
  StmtBlock::Ptr stmt_block = nd->body();
  if (stmt_block != NULL) {
    stmt_block->apply(this);
  }

  Type::Ptr return_type = nd->returnType();
  return_type->apply(this);
}

void
SemanticAnalyser::NodeFunctor::operator()(ClassDecl *nd) {
  inherit_base_class_scopes(nd);
  inherit_interface_scopes(nd);

  Decl::Ptr decl;
  ClassDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(InterfaceDecl *nd) {
  FnDecl::Ptr fn_decl;
  InterfaceDecl::const_member_iter it = nd->membersBegin();
  for (; it != nd->membersEnd(); ++it) {
    fn_decl = *it;
    fn_decl->apply(this);
  }
}

/* -- stmt -- */

void
SemanticAnalyser::NodeFunctor::operator()(StmtBlock *nd) {
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
}


/* stmt/conditional */

void
SemanticAnalyser::NodeFunctor::operator()(ConditionalStmt *nd) {
  Stmt::Ptr body = nd->body();
  body->apply(this);
}

void
SemanticAnalyser::NodeFunctor::operator()(IfStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);

  Stmt::Ptr else_body = nd->elseBody();
  if (else_body != NULL) {
    else_body->apply(this);
  }
}


/* stmt/conditional/loop */
void
SemanticAnalyser::NodeFunctor::operator()(ForStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);
}

void
SemanticAnalyser::NodeFunctor::operator()(WhileStmt *nd) {
  ConditionalStmt *cond_stmt = nd;
  (*this)(cond_stmt);
}


/* type */
void
SemanticAnalyser::NodeFunctor::operator()(NamedType *nd) {
  /* named type identifier */
  Identifier::Ptr type_id = nd->identifier();

  Scope::Ptr scope = nd->scope();
  ClassDecl::Ptr class_decl = scope->classDecl(type_id);
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
  type->apply(this);
}


/* SemanticAnalyser private member functions */

void
SemanticAnalyser::NodeFunctor::
inherit_base_class_scopes(ClassDecl::Ptr nd, IdentifierSet::Ptr _seen) {
  if (nd->scopeIndexed())
    return;

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
    } else {
      Error::IdentifierNotDeclared(base_id, kLookingForClass);
    }
  }

  nd->scopeIndexedIs(true);
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
      intf_scope = intf_decl->scope();
      scope->baseScopeIs(intf_scope);
    } else {
      Error::IdentifierNotDeclared(base_id, kLookingForInterface);
    }
  }
}
