#ifndef NULL_EXPR_H_LG6PDF2A
#define NULL_EXPR_H_LG6PDF2A

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Type;

class NullConstExpr: public Expr {
public:
  typedef Simone::Ptr<const NullConstExpr> PtrConst;
  typedef Simone::Ptr<NullConstExpr> Ptr;

  static Ptr NullConstExprNew(yyltype loc) {
    return new NullConstExpr(loc);
  }

  NullConstExpr(yyltype loc) : Expr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
