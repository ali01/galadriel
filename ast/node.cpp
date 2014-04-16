#include "node.h"

/* stl includes */
#include <string>

/* project includes */
#include <scope/scope.h>

/* ast/stmt includes */
#include "stmt/stmt.h"

/* ast/stmt/conditional/loop includes */
#include "stmt/conditional/loop/loop_stmt.h"

/* ast/decl includes */
#include "decl/decl.h"
#include "decl/object/class_decl.h"

Node::Node(yyltype loc) {
  lex_location_  = new yyltype(loc);
}

Node::Node() {
  lex_location_ = NULL;
}

Node::~Node() {}

Scope::Ptr
Node::scope() {
  return scope_;
}

Scope::PtrConst
Node::scope() const {
  return scope_;
}

void
Node::scopeIs(Scope::Ptr _s) {
  scope_ = _s;
}

ClassDecl::PtrConst
Node::nearestClass() const {
  ClassDecl::PtrConst class_decl = NULL;
  if (parent_)
    class_decl = parent_->nearestClass();

  return class_decl;
}

FnDecl::PtrConst
Node::nearestFunction() const {
  FnDecl::PtrConst fn_decl = NULL;
  if (parent_)
    fn_decl = parent_->nearestFunction();

  return fn_decl;
}

LoopStmt::PtrConst
Node::nearestLoop() const {
  LoopStmt::PtrConst loop_stmt = NULL;
  if (parent_)
    loop_stmt = parent_->nearestLoop();

  return loop_stmt;
}
