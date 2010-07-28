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
      void operator()(const Identifier *);
      void operator()(const Operator *);


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

      /* stmt/expr */
      void operator()(const AssignExpr *);
      void operator()(const CallExpr *);
      void operator()(const EmptyExpr *);
      void operator()(const NullExpr *);

      /* stmt/expr/single_addr */
      void operator()(const BoolConstExpr *);
      void operator()(const IntConstExpr *);
      void operator()(const DblConstExpr *);
      void operator()(const StrConstExpr *);
      void operator()(const NewExpr *);
      void operator()(const NewArrayExpr *);
      void operator()(const ReadLineExpr *);

      /* stmt/expr/single_addr/compound */
      void operator()(const ArithmeticExpr *);
      void operator()(const EqualityExpr *);
      void operator()(const LogicalExpr *);
      void operator()(const RelationalExpr *);
      void operator()(const PostfixExpr *);

      /* stmt/expr/single_addr/l_value */
      void operator()(const ArrayAccessExpr *);

      /* stmt/expr/single_addr/l_value/field_access */
      void operator()(const FieldAccessExpr *);
      void operator()(const ThisExpr *);

      /* stmt/switch */
      void operator()(const SwitchStmt *);
      void operator()(const SwitchCaseStmt *);


      /* -- type -- */

      void operator()(const Type *);
      void operator()(const NamedType *);

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
