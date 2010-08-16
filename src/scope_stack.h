#ifndef SCOPE_MAP_H_MVTXPBM6
#define SCOPE_MAP_H_MVTXPBM6

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <scope/scope.h>

class ScopeStack : public Simone::PtrInterface<ScopeStack> {
public:
  typedef Simone::Ptr<const ScopeStack> PtrConst;
  typedef Simone::Ptr<ScopeStack> Ptr;

  static Ptr ScopeStackNew() {
    return new ScopeStack();
  }

  Scope::Ptr scopeNew();
  void scopePop();

private:
  ScopeStack() {}
  Scope::Ptr scope() const;

  /* data members */
  Deque<Scope::Ptr> scope_stack_;
};

#endif
