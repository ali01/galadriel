#include "scope_stack.h"

/* stl includes */
#include <string>

/* simone includes */
#include <simone/exception.h>

/* scope includes */
#include <scope_includes.h>

Scope::Ptr
ScopeStack::scopeNew(ScopeType _type) {
  Scope::Ptr scope;

  switch (_type) {
    case kGlobal:
      assert(this->scope() == NULL);
      scope = new GlobalScope();
      break;

    case kObject:
      scope = new ObjectScope(this->scope());
      break;

    case kParam:
      scope = new ParamScope(this->scope());
      break;

    case kLocal:
      scope = new LocalScope(this->scope());
      break;

    default:
      ABORT();
  }

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
