#ifndef EMPTY_EXPR_H_J2U1TJ24
#define EMPTY_EXPR_H_J2U1TJ24

/* simone includes */
#include <simone/ptr_interface.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Type;

/* This node type is used for those places where an expression is optional.
 * We could use a NULL pointer, but then it adds a lot of checking for
 * NULL. By using a valid, but no-op, node, we save that trouble */
class EmptyExpr : public Expr {
public:
  typedef Simone::Ptr<const EmptyExpr> PtrConst;
  typedef Simone::Ptr<EmptyExpr> Ptr;

  static Ptr EmptyExprNew() {
    return new EmptyExpr();
  }

  EmptyExpr() : Expr() {}

  Simone::Ptr<const Type> type() const;
  Simone::Ptr<Location> location() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
