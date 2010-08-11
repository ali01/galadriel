#ifndef INT_CONSTANT_H_BNDXZ4HE
#define INT_CONSTANT_H_BNDXZ4HE

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Type;

class IntConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const IntConstExpr> PtrConst;
  typedef Simone::Ptr<IntConstExpr> Ptr;

  static Ptr IntConstExprNew(yyltype loc, int val) {
    return new IntConstExpr(loc, val);
  }

  IntConstExpr(yyltype loc, int val) : SingleAddrExpr(loc) { value = val; }

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:  
  /* data members */
  int value;
};

#endif
