#ifndef COMPOUND_EXPR_H_9BBM4SJA
#define COMPOUND_EXPR_H_9BBM4SJA

/* single-addr includes */
#include "../single_addr_expr.h"

/* forward declarations */
class Expr;
class Operator;

class CompoundExpr : public SingleAddrExpr {
public:
  /* binary compound expression */
  CompoundExpr(Expr *lhs, Operator *op, Expr *rhs);

  /* postfix unary compound expression */
  CompoundExpr(Operator *op, Expr *rhs);

  /* prefix unary compound expression */
  CompoundExpr(Expr *lhs, Operator *o);

protected:
  Operator *op;
  Expr *left, *right; // left will be NULL if unary
};

#endif
