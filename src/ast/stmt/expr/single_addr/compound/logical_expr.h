#ifndef LOGICAL_EXPR_H_PJQTLHPZ
#define LOGICAL_EXPR_H_PJQTLHPZ

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;
class Type;

class LogicalExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const LogicalExpr> PtrConst;
  typedef Simone::Ptr<LogicalExpr> Ptr;

  static Ptr LogicalExprNew(Expr::Ptr lhs,
                            Simone::Ptr<Operator> op,
                            Expr::Ptr rhs) {
    return new LogicalExpr(lhs, op, rhs);
  }

  LogicalExpr(Expr::Ptr lhs, Simone::Ptr<Operator> op, Expr::Ptr rhs);

  LogicalExpr(Simone::Ptr<Operator> op, Expr::Ptr rhs) : CompoundExpr(op,rhs) {}

  Simone::Ptr<const Type> type() const;
  Simone::Ptr<const Location> location();

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
