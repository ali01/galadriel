#ifndef POST_FIX_EXPR_H_YC5FLHWV
#define POST_FIX_EXPR_H_YC5FLHWV

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/single_addr/compound includes */
#include "compound_expr.h"

/* ast/stmt/expr/single_addr includes */
#include "../l_value/l_value_expr.h"

/* forward declarations */
class LValueExpr;
class Operator;

class PostfixExpr : public CompoundExpr {
public:
  typedef Simone::Ptr<const PostfixExpr> PtrConst;
  typedef Simone::Ptr<PostfixExpr> Ptr;

  static Ptr PostfixExprNew(Simone::Ptr<LValueExpr> lhs,
                            Simone::Ptr<Operator> op) {
    return new PostfixExpr(lhs, op);
  }

  PostfixExpr(Simone::Ptr<LValueExpr> lhs,
              Simone::Ptr<Operator> op) : CompoundExpr(lhs, op) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }
};

#endif
