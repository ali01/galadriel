#ifndef THIS_H_AWIFBXRQ
#define THIS_H_AWIFBXRQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/l_value includes */
#include "expr.h"

class ThisExpr : public Expr {
public:
  typedef Simone::Ptr<const ThisExpr> PtrConst;
  typedef Simone::Ptr<ThisExpr> Ptr;

  static Ptr ThisExprNew() {
    struct yyltype loc;
    memset(&loc, 0x0, sizeof loc);
    return new ThisExpr(loc);
  }

  static Ptr ThisExprNew(yyltype loc) {
    return new ThisExpr(loc);
  }

  ThisExpr(yyltype loc) : Expr(loc) {}

  Simone::Ptr<const Type> type() const;
  Simone::Ptr<Location> location() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
