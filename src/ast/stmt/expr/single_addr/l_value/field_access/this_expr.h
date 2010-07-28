#ifndef THIS_H_AWIFBXRQ
#define THIS_H_AWIFBXRQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr/l_value/field_access includes */
#include "field_access_expr.h"

// TODO: consider if should inherit from FieldAccessExpr or not
class ThisExpr : public FieldAccessExpr {
public:
  typedef Simone::Ptr<const ThisExpr> PtrConst;
  typedef Simone::Ptr<ThisExpr> Ptr;

  static Ptr ThisExprNew(yyltype loc) {
    return new ThisExpr(loc);
  }

  ThisExpr(yyltype loc) : FieldAccessExpr(loc) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }
};

#endif
