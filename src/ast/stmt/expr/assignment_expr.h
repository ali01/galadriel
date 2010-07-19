#ifndef ASSIGNMENT_EXPR_H_CIV2NE6Y
#define ASSIGNMENT_EXPR_H_CIV2NE6Y

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Expr;

class AssignExpr : public Expr {
public:
  AssignExpr(Expr *lhs, Expr *rhs);

private:
  /* data members */
  Expr *left, *right;
};

#endif
