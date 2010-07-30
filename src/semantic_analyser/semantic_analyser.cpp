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
SemanticAnalyser::NodeFunctor::operator()(FnDecl *nd) {
  VarDecl::Ptr decl;
  FnDecl::const_formal_iter it = nd->formalsBegin();
  for (; it != nd->formalsEnd(); ++it) {
    decl = *it;
    decl->apply(this);
  }

  StmtBlock::Ptr stmt_block = nd->body();

  /* stmt_block could be NULL in the case of a function prototype */
  if (stmt_block != NULL) {
    stmt_block->apply(this);
  }
}

void
SemanticAnalyser::NodeFunctor::operator()(ClassDecl *nd) {
  NamedType::Ptr base_class_type = nd->baseClass();
  if (base_class_type != NULL) {
    /* obtain class's parent-scope (i.e. the global scope) */
    Scope::Ptr scope = nd->scope();
    Scope::PtrConst parent_scope = scope->parentScope();

    /* search for base class identifier in parent scope */
    Identifier::Ptr base_id = base_class_type->identifier();
    ClassDecl::PtrConst base_decl = parent_scope->classDecl(base_id);

    if (base_decl != NULL) {
      /* inherit from base scope */
      Scope::PtrConst base_scope = base_decl->scope();
      scope->baseScopeIs(base_scope);
    } else {
      Error::IdentifierNotDeclared(base_id, kLookingForClass);
    }
  }

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
