#ifndef ARITHMETIC_EXPR_H_DY36JD54
#define ARITHMETIC_EXPR_H_DY36JD54

/* ast/stmt/expr/singl_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

class ArithmeticExpr : public CompoundExpr {
public:
  ArithmeticExpr(Expr *lhs, Operator *op, Expr *rhs);
  ArithmeticExpr(Operator *op, Expr *rhs) : CompoundExpr(op, rhs) {}
};

#endif
