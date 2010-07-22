#ifndef NEW_ARRAY_EXPR_H_MSJQ9O4H
#define NEW_ARRAY_EXPR_H_MSJQ9O4H

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Expr;
class NamedType;
class Type;

class NewArrayExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const NewArrayExpr> PtrConst;
  typedef Simone::Ptr<NewArrayExpr> Ptr;

  static Ptr NewArrayExprNew(yyltype loc,
                             Expr::Ptr size_expr,
                             Simone::Ptr<Type> elem_type) {
    return new NewArrayExpr(loc, size_expr, elem_type);
  }

  NewArrayExpr(yyltype loc,
               Expr::Ptr size_expr,
               Simone::Ptr<Type> sive_expr);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Expr::Ptr size_;
  Simone::Ptr<Type> elem_type_;
};

#endif
