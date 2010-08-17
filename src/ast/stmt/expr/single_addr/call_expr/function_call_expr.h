#ifndef CALL_H_D5Q44BY5
#define CALL_H_D5Q44BY5

/* ast/stmt/expr/call_expr.h includes */
#include "call_expr.h"

/* forward declarations */
class Identifier;
class FnDecl;

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().    We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */

class FunctionCallExpr : public CallExpr {
public:
  typedef Simone::Ptr<const FunctionCallExpr> PtrConst;
  typedef Simone::Ptr<FunctionCallExpr> Ptr;

  static Ptr FunctionCallExprNew(yyltype _loc,
                                 Simone::Ptr<Identifier> _identifier,
                                 Deque<Expr::Ptr>::Ptr _args) {
    return new FunctionCallExpr(_loc, _identifier, _args);
  }


  FunctionCallExpr(yyltype _loc,
                   Simone::Ptr<Identifier> _identifier,
                   Deque<Expr::Ptr>::Ptr _args);


  Simone::Ptr<const FnDecl> fnDecl() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
