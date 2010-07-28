#ifndef CALL_H_D5Q44BY5
#define CALL_H_D5Q44BY5

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Identifier;

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().    We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */

class CallExpr : public Expr {
public:
  typedef Simone::Ptr<const CallExpr> PtrConst;
  typedef Simone::Ptr<CallExpr> Ptr;

  static Ptr CallExprNew(yyltype loc,
                         Expr::Ptr base,
                         Simone::Ptr<Identifier> field,
                         Deque<Expr::Ptr>::Ptr args) {
    return new CallExpr(loc, base, field, args);
  }
  

  CallExpr(yyltype loc,
           Expr::Ptr base,
           Simone::Ptr<Identifier> field,
           Deque<Expr::Ptr>::Ptr args);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  /* base will be null if no explicit base */
  Expr::Ptr base;
  Simone::Ptr<Identifier> field;
  Deque<Expr::Ptr>::Ptr actuals;
  /* data type compatible with return type of field */
};

#endif
