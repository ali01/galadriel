#ifndef STRING_CONSTANT_H_5V21HZS6
#define STRING_CONSTANT_H_5V21HZS6

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class StrConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const StrConstExpr> PtrConst;
  typedef Simone::Ptr<StrConstExpr> Ptr;

  static Ptr StrConstExprNew(yyltype loc, const char *v) {
    return new StrConstExpr(loc, v);
  }

  StrConstExpr(yyltype loc, const char *v);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  /* data members */
  char *value;
};

#endif
