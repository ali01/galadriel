#ifndef LOCAL_SCOPE_H_E1D2PN7O
#define LOCAL_SCOPE_H_E1D2PN7O

/* simone includes */
#include <simone/utility.h>

/* local includes */
#include "scope.h"

/* forward declarations */
class TmpLocation;

class LocalScope : public Scope {
public:
  typedef Simone::Ptr<const LocalScope> PtrConst;
  typedef Simone::Ptr<LocalScope> Ptr;

  static const int kLocalsOffset = -2;

  Simone::Ptr<const TmpLocation> tempNew();

private:
  LocalScope(Scope::Ptr _parent_scope);

  /* double dispatch */
  class NodeFunctor : public Scope::NodeFunctor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(LocalScope::Ptr _s) {
        return new NodeFunctor(_s);
      }

      /* overrides */
      void operator()(VarDecl *_d);
      void operator()(FnDecl *_d) { ABORT(); }
      void operator()(ClassDecl *_d) { ABORT(); }
      void operator()(InterfaceDecl *_d) { ABORT(); }

    private:
      explicit NodeFunctor(LocalScope::Ptr _s) : Scope::NodeFunctor(_s) {}
  };

  /* data members */

  /* operations disallowed */
  LocalScope(const LocalScope&);
  void operator=(const LocalScope&);

  /* friends */
  friend class ScopeStack;
};


#endif
