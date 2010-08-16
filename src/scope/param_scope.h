#ifndef PARAM_SCOPE_H_PMUTWLK4
#define PARAM_SCOPE_H_PMUTWLK4

/* simone includes */
#include <simone/utility.h>

/* local includes */
#include "scope.h"

class ParamScope : public Scope {
public:
  typedef Simone::Ptr<const ParamScope> PtrConst;
  typedef Simone::Ptr<ParamScope> Ptr;

  static const int kParamsOffset = 1;

private:
  ParamScope(Scope::Ptr _parent_scope);

  /* double dispatch */
  class NodeFunctor : public Scope::NodeFunctor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(ParamScope::Ptr _s) {
        return new NodeFunctor(_s);
      }

      /* overrides */
      void operator()(VarDecl *_d);
      void operator()(FnDecl *_d) { ABORT(); }
      void operator()(ClassDecl *_d) { ABORT(); }
      void operator()(InterfaceDecl *_d) { ABORT(); }

    private:
      explicit NodeFunctor(ParamScope::Ptr _s) : Scope::NodeFunctor(_s) {}
  };

  /* data members */

  /* operations disallowed */
  ParamScope(const ParamScope&);
  void operator=(const ParamScope&);

  /* friends */
  friend class ScopeStack;
};

#endif
