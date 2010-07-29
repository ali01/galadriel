#ifndef LOCAL_SCOPE_H_28DYDUSQ
#define LOCAL_SCOPE_H_28DYDUSQ

/* project includes */
#include "scope.h"

class LocalScope : public Scope {
public:
  typedef Simone::Ptr<const LocalScope> PtrConst;
  typedef Simone::Ptr<LocalScope> Ptr;

  static Ptr LocalScopeNew() {
    return new LocalScope();
  }

  /* override base class version to disallow replacement */
  void declIs(Decl::PtrConst _decl);

private:
  LocalScope() {}
};

#endif
