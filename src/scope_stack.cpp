#include "scope_stack.h"

/* stl includes */
#include <string>

/* simone includes */
#include <simone/exception.h>

Scope::Ptr
ScopeStack::scope() const {
  Scope::Ptr scope = NULL;
  if (scope_stack_.size() > 0)
    scope = scope_stack_.back();

  return scope;
}

Scope::Ptr
ScopeStack::scopeNew() {
  Scope::Ptr scope = new Scope();
  scope_stack_.pushBack(scope);
  // TODO: copy parent scope
  return scope;
}

void
ScopeStack::scopeDel() {
  if (scope_stack_.size() > 0) {
    scope_stack_.popBack();
  } else {
    string msg = "scopeDel() called on empty ScopeStack";
    throw Simone::RangeException(__FILE__, __LINE__, msg);
  }
}
