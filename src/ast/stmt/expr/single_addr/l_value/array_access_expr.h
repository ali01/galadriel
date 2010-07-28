#ifndef ARRAY_ACCESS_H_M0ABFQJ4
#define ARRAY_ACCESS_H_M0ABFQJ4

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"

/* forward declarations */
class Expr;

class ArrayAccessExpr : public LValueExpr {
public:
  typedef Simone::Ptr<const ArrayAccessExpr> PtrConst;
  typedef Simone::Ptr<ArrayAccessExpr> Ptr;

  static Ptr ArrayAccessExprNew(yyltype loc,
                                Expr::Ptr base,
                                Expr::Ptr subscript) {
    return new ArrayAccessExpr(loc, base, subscript);
  }
  

  ArrayAccessExpr(yyltype loc, Expr::Ptr base, Expr::Ptr subscript);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  Expr::Ptr base, subscript;
};

#endif
