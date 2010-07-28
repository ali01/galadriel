#ifndef DOUBLE_CONSTANT_H_CG464C3B
#define DOUBLE_CONSTANT_H_CG464C3B

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class DblConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const DblConstExpr> PtrConst;
  typedef Simone::Ptr<DblConstExpr> Ptr;

  static Ptr DblConstExprNew(yyltype loc , double v) {
    return new DblConstExpr(loc, v);
  }

  DblConstExpr(yyltype loc, double v) : SingleAddrExpr(loc) { value = v; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  /* data members */
  double value;
};

#endif
