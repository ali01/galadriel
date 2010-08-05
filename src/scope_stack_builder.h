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
      
      /* operators that are not overriden appear as comments */

      /* top level */
      /* void operator()(Node *); */
      void operator()(Program *);
      /* void operator()(Identifier *); */
      /* void operator()(Operator *); */

      /* decl */
      void operator()(Decl *);
      void operator()(VarDecl *);
      void operator()(FnDecl *);
      void operator()(ClassDecl *);
      void operator()(InterfaceDecl *);

      /* stmt */
      /* void operator()(Stmt *); */
      void operator()(StmtBlock *);
      void operator()(PrintStmt *);
      void operator()(ReturnStmt *);
      /* void operator()(BreakStmt *); */

      /* stmt/conditional */
      void operator()(ConditionalStmt *);
      void operator()(IfStmt *);

      /* stmt/conditional/loop */
      /* void operator()(LoopStmt *); */
      void operator()(ForStmt *);
      void operator()(WhileStmt *);

      /* stmt/expr */
      /* void operator()(Expr *); */
      void operator()(AssignExpr *);
      void operator()(CallExpr *);
      /* void operator()(NullExpr *); */
      /* void operator()(EmptyExpr *); */

      /* stmt/expr/single_addr */
      /* void operator()(SingleAddrExpr *); */
      /* void operator()(BoolConstExpr *); */
      /* void operator()(IntConstExpr *); */
      /* void operator()(DblConstExpr *); */
      /* void operator()(StrConstExpr *); */
      /* void operator()(ReadLineExpr *); */
      /* void operator()(ReadIntegerExpr *); */
      void operator()(NewExpr *);
      void operator()(NewArrayExpr *);

      /* stmt/expr/single_addr/compound */
      void operator()(CompoundExpr *);
      void operator()(ArithmeticExpr *);
      void operator()(LogicalExpr *);
      void operator()(RelationalExpr *);

      /* stmt/expr/single_addr/l_value */
      /* void operator()(LValueExpr *); */
      void operator()(VarAccessExpr *);
      void operator()(ArrayAccessExpr *);
      void operator()(FieldAccessExpr *);
      /* void operator()(ThisExpr *); */

      /* type */
      /* void operator()(Type *); */
      void operator()(NamedType *);
      void operator()(ArrayType *);

    private:
      NodeFunctor(ScopeStack::Ptr _s) : scope_stack_(_s) {}
      
      /* member functions */
      void init_node_scope(Node::Ptr _nd, Node::Ptr _parent, Scope::Ptr _scope);
      
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
