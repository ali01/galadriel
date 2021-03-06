#ifndef NEW_ARRAY_EXPR_H_MSJQ9O4H
#define NEW_ARRAY_EXPR_H_MSJQ9O4H

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Expr;
class Location;
class NamedType;
class ArrayType;
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
               Simone::Ptr<Type> elem_type);

  /* attribute member functions */
  Expr::PtrConst size() const { return size_; }
  Expr::Ptr size() { return size_; }

  Simone::Ptr<const ArrayType> arrayType() const;
  Simone::Ptr<ArrayType> arrayType();

  Simone::Ptr<Location> auxLocation() const;
  void auxLocationIs(Simone::Ptr<Location> _loc);

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Simone::Ptr<const Type> type() const;

  /* data members */
  Expr::Ptr size_;
  Simone::Ptr<ArrayType> type_;
  Simone::Ptr<Location> aux_loc_;
};

#endif
