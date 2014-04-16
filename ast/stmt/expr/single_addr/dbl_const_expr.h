#ifndef DOUBLE_CONSTANT_H_CG464C3B
#define DOUBLE_CONSTANT_H_CG464C3B

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Location;
class Type;

class DblConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const DblConstExpr> PtrConst;
  typedef Simone::Ptr<DblConstExpr> Ptr;

  static Ptr DblConstExprNew(yyltype loc , double v) {
    return new DblConstExpr(loc, v);
  }

  DblConstExpr(yyltype loc, double v) : SingleAddrExpr(loc) { value = v; }

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  double value;
};

#endif
