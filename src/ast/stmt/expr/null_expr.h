#ifndef NULL_EXPR_H_LG6PDF2A
#define NULL_EXPR_H_LG6PDF2A

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Type;

class NullExpr: public Expr {
public:
  typedef Simone::Ptr<const NullExpr> PtrConst;
  typedef Simone::Ptr<NullExpr> Ptr;

  static Ptr NullExprNew(yyltype loc) {
    return new NullExpr(loc);
  }

  NullExpr(yyltype loc) : Expr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
