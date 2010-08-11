#ifndef THIS_H_AWIFBXRQ
#define THIS_H_AWIFBXRQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"

class ThisExpr : public LValueExpr {
public:
  typedef Simone::Ptr<const ThisExpr> PtrConst;
  typedef Simone::Ptr<ThisExpr> Ptr;

  static Ptr ThisExprNew(yyltype loc) {
    return new ThisExpr(loc);
  }

  ThisExpr(yyltype loc) : LValueExpr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
