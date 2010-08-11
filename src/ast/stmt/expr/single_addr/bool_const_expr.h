#ifndef BOOL_CONSTANT_H_ZCPXRQCL
#define BOOL_CONSTANT_H_ZCPXRQCL

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Type;

class BoolConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const BoolConstExpr> PtrConst;
  typedef Simone::Ptr<BoolConstExpr> Ptr;

  static Ptr BoolConstExprNew(yyltype loc, bool val) {
    return new BoolConstExpr(loc, val);
  }

  BoolConstExpr(yyltype loc, bool val) : SingleAddrExpr(loc) { value = val; }

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  bool value;
};


#endif
