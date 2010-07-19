#ifndef POST_FIX_EXPR_H_YC5FLHWV
#define POST_FIX_EXPR_H_YC5FLHWV

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* ast/stmt/expr/single_addr includes */
#include "../l_value/l_value_expr.h"

/* forward declarations */
class LValueExpr;
class Operator;

// TODO: think about SingleAddr business
class PostfixExpr : public CompoundExpr {
public:
  PostfixExpr(LValueExpr *lhs, Operator *op) : CompoundExpr(lhs, op) {}
};

#endif
