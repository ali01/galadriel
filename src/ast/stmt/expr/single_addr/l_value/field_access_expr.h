#ifndef FIELD_ACCESS_H_ZGC2WBOI
#define FIELD_ACCESS_H_ZGC2WBOI

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"

/* forward declarations */
class Expr;
class Identifier;
class Type;
class VarDecl;

/* Note that field access is used both for qualified names
 * base.field and just field without qualification. We don't
 * know for sure whether there is an implicit "this." in
 * front until later on, so we use one node type for either
 * and sort it out later. */
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

  Simone::Ptr<Identifier> field();
  Simone::Ptr<const Identifier> field() const;

  Simone::Ptr<const ClassDecl> baseDecl() const;
  Simone::Ptr<const VarDecl> varDecl() const;
  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Expr::Ptr base_; /* will be NULL if no explicit base */
  Simone::Ptr<Identifier> field_;
};

#endif
