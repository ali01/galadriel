#include "node.h"

/* stl includes */
#include <string>

/* project includes */
#include <scope.h>

/* ast/stmt includes */
#include "stmt/stmt.h"

/* ast/stmt/conditional/loop includes */
#include "stmt/conditional/loop/loop_stmt.h"

/* ast/decl includes */
#include "decl/decl.h"
#include "decl/class_decl.h"

Node::Node(yyltype loc) {
  location  = new yyltype(loc);
}

Node::Node() {
  location = NULL;
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
Node::enclosingClass() const {
  ClassDecl::PtrConst class_decl = NULL;
  if (parent_)
    class_decl = parent_->enclosingClass();

  return class_decl;
}

FnDecl::PtrConst
Node::enclosingFunction() const {
  FnDecl::PtrConst fn_decl = NULL;
  if (parent_)
    fn_decl = parent_->enclosingFunction();

  return fn_decl;
}

LoopStmt::PtrConst
Node::enclosingLoop() const {
  LoopStmt::PtrConst loop_stmt = NULL;
  if (parent_)
    loop_stmt = parent_->enclosingLoop();

  return loop_stmt;
}
