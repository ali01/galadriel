#ifndef COMPILER_H_VO9YQUZS
#define COMPILER_H_VO9YQUZS

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/set.h>
using Simone::Set;

/* ast includes */
#include <ast/node.h>
#include <ast/identifier.h>

/* forward declarations */
class Program;
class ScopeStackBuilder;

class SemanticAnalyser : public Simone::PtrInterface<SemanticAnalyser> {
  /* private typedefs */
  typedef Set<Identifier::PtrConst,Identifier::less> IdentifierSet;
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

      /* top level */
      void operator()(Program *);
      /* void operator()(Identifier *); */
      /* void operator()(Operator *); */

      /* decl */
      void operator()(Decl *);
      void operator()(VarDecl *);
      void operator()(FnDecl *);

      /* decl/object */
      void operator()(ObjectDecl *);
      void operator()(ClassDecl *);
      void operator()(InterfaceDecl *);

      /* stmt */
      /* void operator()(Stmt *); */
      void operator()(StmtBlock *);
      void operator()(PrintStmt *);
      void operator()(ReturnStmt *);
      void operator()(BreakStmt *);

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
      /* void operator()(EmptyExpr *); */
      void operator()(ThisExpr *);

      /* stmt/expr/l_value */
      /* void operator()(LValueExpr *); */
      void operator()(VarAccessExpr *);
      void operator()(ArrayAccessExpr *);
      void operator()(FieldAccessExpr *);

      /* stmt/expr/single_addr */
      /* void operator()(SingleAddrExpr *); */
      /* void operator()(BoolConstExpr *); */
      /* void operator()(IntConstExpr *); */
      /* void operator()(DblConstExpr *); */
      /* void operator()(StrConstExpr *); */
      /* void operator()(NullConstExpr *); */
      /* void operator()(ReadLineExpr *); */
      /* void operator()(ReadIntegerExpr *); */
      void operator()(NewExpr *);
      void operator()(NewArrayExpr *);

      /* stmt/expr/single_addr/call_expr */
      void operator()(CallExpr *);
      void operator()(FunctionCallExpr *);
      void operator()(MethodCallExpr *);

      /* stmt/expr/single_addr/compound */
      void operator()(CompoundExpr *);
      void operator()(ArithmeticExpr *);
      void operator()(LogicalExpr *);
      void operator()(RelationalExpr *);

      /* type */
      /* void operator()(Type *); */
      void operator()(NamedType *);
      void operator()(ArrayType *);

    private:
      NodeFunctor() {}

      /* member functions */
      void process_node(Node::Ptr _nd);

      bool inheritance_contains_cycles(Simone::Ptr<ClassDecl> nd,
                                       IdentifierSet::Ptr _seen=NULL);
      void inherit_base_class_scopes(Simone::Ptr<ClassDecl> nd);
      void inherit_interface_scopes(Simone::Ptr<ClassDecl> nd);

      static void verify_args_match(Simone::Ptr<const CallExpr> nd,
                                    Simone::Ptr<const FnDecl> fn_decl);
  };

  /* data members */
  Simone::Ptr<ScopeStackBuilder> sm_builder_;
  NodeFunctor::Ptr node_functor_;
  
  /* operations disallowed */
  SemanticAnalyser(const SemanticAnalyser&);
  void operator=(const SemanticAnalyser&);
};

#endif
