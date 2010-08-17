#ifndef FIELD_ACCESS_H_ZGC2WBOI
#define FIELD_ACCESS_H_ZGC2WBOI

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr/l_value includes */
#include "l_value_expr.h"

/* forward declarations */
class Expr;
class Identifier;

class FieldAccessExpr : public LValueExpr {
public:
  typedef Simone::Ptr<const FieldAccessExpr> PtrConst;
  typedef Simone::Ptr<FieldAccessExpr> Ptr;

  static Ptr FieldAccessExprNew(Expr::Ptr base, Simone::Ptr<Identifier> field) {
    return new FieldAccessExpr(base, field);
  }

  /* ok to pass in NULL base */
  FieldAccessExpr(Expr::Ptr base, Simone::Ptr<Identifier> field);

  /* attribute member functions */
  Expr::Ptr base() { return base_; }
  Expr::PtrConst base() const { return base_; }

  Simone::Ptr<Identifier> identifier();
  Simone::Ptr<const Identifier> identifier() const;

  Simone::Ptr<const ClassDecl> baseDecl() const;
  Simone::Ptr<const VarDecl> varDecl() const; /* override */

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  Expr::Ptr base_;
  Simone::Ptr<Identifier> identifier_;
};

#endif
