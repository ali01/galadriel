#ifndef LOGICAL_EXPR_H_PJQTLHPZ
#define LOGICAL_EXPR_H_PJQTLHPZ

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

class LogicalExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const LogicalExpr> PtrConst;
  typedef Simone::Ptr<LogicalExpr> Ptr;

  static Ptr LogicalExprNew(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) {
    return new LogicalExpr(lhs, op, rhs);
  }

  LogicalExpr(Expr::Ptr lhs, Operator::Ptr op, Expr::Ptr rhs) : 
    CompoundExpr(lhs,op,rhs) {}

  LogicalExpr(Operator::Ptr op, Expr::Ptr rhs) : CompoundExpr(op,rhs) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
