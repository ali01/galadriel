#ifndef METHOD_CALL_EXPR_H_I2R1ZK8J
#define METHOD_CALL_EXPR_H_I2R1ZK8J

/* ast/stmt/expr/call_expr.h includes */
#include "call_expr.h"

/* forward declarations */
class FnDecl;
class ObjectDecl;

class MethodCallExpr : public CallExpr {
public:
  typedef Simone::Ptr<const MethodCallExpr> PtrConst;
  typedef Simone::Ptr<MethodCallExpr> Ptr;

  static Ptr MethodCallExprNew(yyltype _loc,
                               Expr::Ptr _base,
                               Simone::Ptr<Identifier> _method,
                               Deque<Expr::Ptr>::Ptr _args) {
    return new MethodCallExpr(_loc, _base, _method, _args);
  }

  MethodCallExpr(yyltype _loc,
                 Expr::Ptr _base,
                 Simone::Ptr<Identifier> _method,
                 Deque<Expr::Ptr>::Ptr _args);

  /* attribute member functions */
  Expr::Ptr base() { return base_; }
  Expr::PtrConst base() const { return base_; }

  Simone::Ptr<const ObjectDecl> baseDecl() const; /* can return NULL */
  Simone::Ptr<const FnDecl> fnDecl() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  class BaseDeclFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const BaseDeclFunctor> PtrConst;
      typedef Simone::Ptr<BaseDeclFunctor> Ptr;

      static Ptr BaseDeclFunctorNew(MethodCallExpr::Ptr _call_expr) {
        return new BaseDeclFunctor(_call_expr);
      }

      Simone::Ptr<ObjectDecl> baseDecl() const;

      void operator()(NamedType *);
      void operator()(ArrayType *);

    private:
      BaseDeclFunctor(MethodCallExpr::Ptr _call_expr) :
        call_expr_(_call_expr) {}

      /* data members */
      Simone::Ptr<ObjectDecl> base_decl_;
      MethodCallExpr::Ptr call_expr_;
  };

  /* data members */
  Expr::Ptr base_;

  BaseDeclFunctor::Ptr base_decl_functor_;

  /* disallowed operations */
  MethodCallExpr(const MethodCallExpr&);
  void operator=(const MethodCallExpr&);
};


#endif
