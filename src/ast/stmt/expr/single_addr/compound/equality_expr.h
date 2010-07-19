#ifndef EQUALITY_EXPR_H_3FNFKGN2
#define EQUALITY_EXPR_H_3FNFKGN2

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

// TODO: think about inheriting from RelationalExpr
class EqualityExpr : public CompoundExpr {
public:
  EqualityExpr(Expr *lhs, Operator *op, Expr *rhs) : CompoundExpr(lhs,op,rhs) {}
};

#endif
