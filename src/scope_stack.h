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

  enum ScopeType { kGlobal, kObject, kParam, kLocal };

  static Ptr ScopeStackNew() {
    return new ScopeStack();
  }

  Scope::Ptr scopeNew(ScopeType _type);
  void scopePop();

private:
  ScopeStack() {}

  /* member functions */
  Scope::Ptr scope() const;

  /* data members */
  Deque<Scope::Ptr> scope_stack_;
};

#endif
