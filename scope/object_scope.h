#ifndef OBJECT_SCOPE_H_KUKBNDB3
#define OBJECT_SCOPE_H_KUKBNDB3

/* simone includes */
#include <simone/utility.h>

/* local includes */
#include "scope.h"

class ObjectScope : public Scope {
public:
  typedef Simone::Ptr<const ObjectScope> PtrConst;
  typedef Simone::Ptr<ObjectScope> Ptr;

private:
  ObjectScope(Scope::Ptr _parent_scope);

  /* double dispatch */
  class NodeFunctor : public Scope::NodeFunctor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(ObjectScope::Ptr _s) {
        return new NodeFunctor(_s);
      }

      /* overrides */
      void operator()(VarDecl *_d);
      void operator()(ClassDecl *_d) { ABORT(); }
      void operator()(InterfaceDecl *_d) { ABORT(); }

    private:
      explicit NodeFunctor(ObjectScope::Ptr _s) : Scope::NodeFunctor(_s) {}
  };

  bool isObjectScope() const { return true; }

  /* data members */

  /* operations disallowed */
  ObjectScope(const ObjectScope&);
  void operator=(const ObjectScope&);

  /* friends */
  friend class ScopeStack;
};

#endif
