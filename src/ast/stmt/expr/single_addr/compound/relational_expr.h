#ifndef RELATIONAL_EXPR_H_4GKQLWZF
#define RELATIONAL_EXPR_H_4GKQLWZF

/* ast/stmt/expr/single_addr/compound */
#include "compound_expr.h"

/* forward declarations */
class Expr;
class Operator;

class RelationalExpr : public CompoundExpr {
public:
  RelationalExpr(Expr *lhs, Operator *op, Expr *rhs);
};

#endif
