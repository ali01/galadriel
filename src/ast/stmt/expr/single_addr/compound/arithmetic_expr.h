#ifndef ARITHMETIC_EXPR_H_DY36JD54
#define ARITHMETIC_EXPR_H_DY36JD54

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

class ArithmeticExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const ArithmeticExpr> PtrConst;
  typedef Simone::Ptr<ArithmeticExpr> Ptr;

  static Ptr ArithmeticExprNew(Simone::Ptr<Expr> lhs,
                               Simone::Ptr<Operator> op,
                               Simone::Ptr<Expr> rhs) {
    return new ArithmeticExpr(lhs, op, rhs);
  }

  static Ptr ArithmeticExprNew(Simone::Ptr<Operator> op,
                               Simone::Ptr<Expr> rhs) {
    return new ArithmeticExpr(op, rhs);
  }

  ArithmeticExpr(Simone::Ptr<Expr> lhs,
                 Simone::Ptr<Operator> op,
                 Simone::Ptr<Expr> rhs);
  ArithmeticExpr(Simone::Ptr<Operator> op,
                 Simone::Ptr<Expr> rhs) : CompoundExpr(op, rhs) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }
};

#endif
