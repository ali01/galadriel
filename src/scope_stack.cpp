#include "scope_stack.h"

/* stl includes */
#include <string>

/* simone includes */
#include <simone/exception.h>

Scope::Ptr
ScopeStack::scopeNew() {
  Scope::Ptr scope = new Scope(this->scope());
  scope_stack_.pushBack(scope);
  return scope;
}

void
ScopeStack::scopePop() {
  if (scope_stack_.size() > 0) {
    scope_stack_.popBack();
  } else {
    string msg = "scopePop() called on empty ScopeStack";
    throw Simone::RangeException(__FILE__, __LINE__, msg);
  }
}

/* private interface */

Scope::Ptr
ScopeStack::scope() const {
  Scope::Ptr scope = NULL;
  if (scope_stack_.size() > 0)
    scope = scope_stack_.back();

  return scope;
}
