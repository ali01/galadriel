#ifndef EQUALITY_EXPR_H_3FNFKGN2
#define EQUALITY_EXPR_H_3FNFKGN2

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

// TODO: think about inheriting from RelationalExpr
class EqualityExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const EqualityExpr> PtrConst;
  typedef Simone::Ptr<EqualityExpr> Ptr;

  static Ptr EqualityExprNew(Simone::Ptr<Expr> lhs,
                             Simone::Ptr<Operator> op,
                             Simone::Ptr<Expr> rhs) {
    return new EqualityExpr(lhs, op, rhs);
  }
  
  
  EqualityExpr(Simone::Ptr<Expr> lhs,
               Simone::Ptr<Operator> op,
               Simone::Ptr<Expr> rhs) : CompoundExpr(lhs,op,rhs) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
