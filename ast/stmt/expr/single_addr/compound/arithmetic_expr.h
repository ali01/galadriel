#ifndef ARITHMETIC_EXPR_H_DY36JD54
#define ARITHMETIC_EXPR_H_DY36JD54

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Operator;
class Type;

class ArithmeticExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const ArithmeticExpr> PtrConst;
  typedef Simone::Ptr<ArithmeticExpr> Ptr;

  static Ptr ArithmeticExprNew(Expr::Ptr lhs,
                               Simone::Ptr<Operator> op,
                               Expr::Ptr rhs) {
    return new ArithmeticExpr(lhs, op, rhs);
  }

  static Ptr ArithmeticExprNew(Simone::Ptr<Operator> op, Expr::Ptr rhs) {
    return new ArithmeticExpr(op, rhs);
  }

  ArithmeticExpr(Expr::Ptr lhs,
                 Simone::Ptr<Operator> op,
                 Expr::Ptr rhs);

  ArithmeticExpr(Simone::Ptr<Operator> op,
                 Expr::Ptr rhs);

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
