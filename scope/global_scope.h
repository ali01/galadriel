#ifndef GLOBAL_SCOPE_H_J6KJ6N6
#define GLOBAL_SCOPE_H_J6KJ6N6

#include "scope.h"

class GlobalScope : public Scope {
public:
  typedef Simone::Ptr<const GlobalScope> PtrConst;
  typedef Simone::Ptr<GlobalScope> Ptr;

private:
  GlobalScope();

  /* double dispatch */
  class NodeFunctor : public Scope::NodeFunctor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(GlobalScope::Ptr _s) {
        return new NodeFunctor(_s);
      }

      void operator()(VarDecl *_d); /* override */

    private:
      explicit NodeFunctor(GlobalScope::Ptr _s) : Scope::NodeFunctor(_s) {}
  };

  /* data members */

  /* operations disallowed */
  GlobalScope(const GlobalScope&);
  void operator=(const GlobalScope&);

  /* friends */
  friend class ScopeStack;
};

#endif
