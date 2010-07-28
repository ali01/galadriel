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

void
ScopeStackBuilder::NodeFunctor::operator()(const Identifier *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const Operator *nd) {
  
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
  stmt_block->apply(this);
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
  for(; decl_it != nd->declsEnd(); ++decl_it) {
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
  
}


/* stmt/conditional/loop */
void
ScopeStackBuilder::NodeFunctor::operator()(const ForStmt *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const WhileStmt *nd) {
  
}


/* stmt/expr */
void
ScopeStackBuilder::NodeFunctor::operator()(const AssignExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const CallExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const EmptyExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const NullExpr *nd) {
  
}


/* stmt/expr/single_addr */
void
ScopeStackBuilder::NodeFunctor::operator()(const BoolConstExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const IntConstExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const DblConstExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const StrConstExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const NewExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const NewArrayExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const ReadLineExpr *nd) {
  
}


/* stmt/expr/single_addr/compound */
void
ScopeStackBuilder::NodeFunctor::operator()(const ArithmeticExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const EqualityExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const LogicalExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const RelationalExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const PostfixExpr *nd) {
  
}


/* stmt/expr/single_addr/l_value */
void
ScopeStackBuilder::NodeFunctor::operator()(const ArrayAccessExpr *nd) {
  
}


/* stmt/expr/single_addr/l_value/field_access */
void
ScopeStackBuilder::NodeFunctor::operator()(const FieldAccessExpr *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const ThisExpr *nd) {
  
}


/* stmt/switch */
void
ScopeStackBuilder::NodeFunctor::operator()(const SwitchStmt *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const SwitchCaseStmt *nd) {
  
}



/* -- type -- */

void
ScopeStackBuilder::NodeFunctor::operator()(const Type *nd) {
  
}

void
ScopeStackBuilder::NodeFunctor::operator()(const NamedType *nd) {
  
}
