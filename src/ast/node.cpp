#include "node.h"

/* stl includes */
#include <string>

/* project includes */
#include <scope.h>

/* ast includes */
#include "stmt/stmt.h"

/* ast/decl includes */
#include "decl/decl.h"

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
