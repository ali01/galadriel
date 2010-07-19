#ifndef EMPTY_EXPR_H_J2U1TJ24
#define EMPTY_EXPR_H_J2U1TJ24

/* ast/stmt/expr includes */
#include "expr.h"

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr {
public:
  EmptyExpr() : Expr() {}
};


#endif
