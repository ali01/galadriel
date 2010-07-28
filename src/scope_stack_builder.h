#ifndef SCOPE_MAP_BUILDER_H_UQ99KCV7
#define SCOPE_MAP_BUILDER_H_UQ99KCV7

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include "ast.h"
#include "scope_stack.h"

/* forward declarations */
class ScopeStack;

class ScopeStackBuilder : public Simone::PtrInterface<ScopeStackBuilder> {
public:
  typedef Simone::Ptr<const ScopeStackBuilder> PtrConst;
  typedef Simone::Ptr<ScopeStackBuilder> Ptr;

  static Ptr ScopeStackBuilderNew(Program::Ptr _program) {
    return new ScopeStackBuilder(_program);
  }

  class NodeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew(ScopeStack::Ptr _s) {
        return new NodeFunctor(_s);
      }
      

      /* -- top level -- */

      void operator()(const Program *);


      /* -- decl -- */

      void operator()(const FnDecl *);
      void operator()(const VarDecl *);

      /* decl/object */
      void operator()(const ClassDecl *);
      void operator()(const InterfaceDecl *);


      /* -- stmt -- */

      void operator()(const StmtBlock *);

      /* stmt/conditional */
      void operator()(const IfStmt *);

      /* stmt/conditional/loop */
      void operator()(const ForStmt *);
      void operator()(const WhileStmt *);

      /* stmt/switch */
      void operator()(const SwitchStmt *);
      void operator()(const SwitchCaseStmt *);


    private:
      NodeFunctor(ScopeStack::Ptr _s) : scope_stack_(_s) {}
      
      /* data members */
      ScopeStack::Ptr scope_stack_;
  };

private:
  ScopeStackBuilder(Program::Ptr _program);
  
  /* data members */
  ScopeStack::Ptr scope_stack_;
  NodeFunctor::Ptr node_functor_;
};

#endif
