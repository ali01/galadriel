#ifndef COMPILER_H_VO9YQUZS
#define COMPILER_H_VO9YQUZS

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include <ast/node.h>

/* forward declarations */
class Program;
class ScopeStackBuilder;

class SemanticAnalyser : public Simone::PtrInterface<SemanticAnalyser> {
public:
  typedef Simone::Ptr<const SemanticAnalyser> PtrConst;
  typedef Simone::Ptr<SemanticAnalyser> Ptr;

  static Ptr SemanticAnalyserNew(Simone::Ptr<Program> _program) {
    return new SemanticAnalyser(_program);
  }

private:
  SemanticAnalyser(Simone::Ptr<Program> _program);

  /* implementation of semantic analyser using double dispatch mechanism */
  class NodeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const NodeFunctor> PtrConst;
      typedef Simone::Ptr<NodeFunctor> Ptr;

      static Ptr NodeFunctorNew() {
        return new NodeFunctor();
      }

      /* -- top level -- */

      void operator()(Program *);


      /* -- decl -- */

      void operator()(FnDecl *);
      void operator()(ClassDecl *);
      void operator()(InterfaceDecl *);


      /* -- stmt -- */

      void operator()(StmtBlock *);

      /* stmt/conditional */
      void operator()(ConditionalStmt *);
      void operator()(IfStmt *);

      /* stmt/conditional/loop */
      void operator()(ForStmt *);
      void operator()(WhileStmt *);

    private:
      NodeFunctor() {}
  };

  /* data members */
  Simone::Ptr<ScopeStackBuilder> sm_builder_;
  NodeFunctor::Ptr node_functor_;
};

#endif
