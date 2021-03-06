#ifndef ARRAY_ACCESS_H_M0ABFQJ4
#define ARRAY_ACCESS_H_M0ABFQJ4

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/l_value includes */
#include "l_value_expr.h"

/* forward declarations */
class Expr;
class Type;

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

  /* attribute member functions */
  Expr::Ptr base() { return base_; }
  Expr::PtrConst base() const { return base_; }

  Expr::Ptr subscript() { return subscript_; }
  Expr::PtrConst subscript() const { return subscript_; }

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Simone::Ptr<const VarDecl> varDecl() const; // TODO: fix inheritance

  /* data members */
  Expr::Ptr base_, subscript_;
};

#endif
