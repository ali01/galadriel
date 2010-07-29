#include "node.h"

/* stl includes */
#include <string>

/* project includes */
#include <scope.h>
#include <local_scope.h>

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
Node::scope() const {
  return scope_;
}

void
Node::scopeIs(Scope::Ptr _s) {
  scope_ = _s;
}

LocalScope::Ptr
Node::localScope() const {
  return local_scope_;
}

bool
Node::localScopeIs(LocalScope::Ptr _s) {
  local_scope_ = _s;
  return true;
}

void
Node::scopesAre(Scope::Ptr _scope, LocalScope::Ptr _local_scope) {
  scopeIs(_scope);
  localScopeIs(_local_scope);
}
