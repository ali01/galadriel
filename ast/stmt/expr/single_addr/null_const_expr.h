#ifndef NULL_EXPR_H_LG6PDF2A
#define NULL_EXPR_H_LG6PDF2A

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/expr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Type;

class NullConstExpr: public SingleAddrExpr {
public:
  typedef Simone::Ptr<const NullConstExpr> PtrConst;
  typedef Simone::Ptr<NullConstExpr> Ptr;

  static Ptr NullConstExprNew(yyltype loc) {
    return new NullConstExpr(loc);
  }

  NullConstExpr(yyltype loc) : SingleAddrExpr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
