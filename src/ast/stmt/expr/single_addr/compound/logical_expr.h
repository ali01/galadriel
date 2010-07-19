#ifndef LOGICAL_EXPR_H_PJQTLHPZ
#define LOGICAL_EXPR_H_PJQTLHPZ

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

class LogicalExpr : public CompoundExpr {
public:
  LogicalExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
  LogicalExpr(Operator *op, Expr *rhs) : CompoundExpr(op,rhs) {}
};

#endif
