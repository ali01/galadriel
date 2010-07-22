#ifndef READ_INTEGER_EXPR_H_DZTNBZO5
#define READ_INTEGER_EXPR_H_DZTNBZO5

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

class ReadIntegerExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const ReadIntegerExpr> PtrConst;
  typedef Simone::Ptr<ReadIntegerExpr> Ptr;

  static Ptr ReadIntegerExprNew(yyltype loc) {
    return new ReadIntegerExpr(loc);
  }

  ReadIntegerExpr(yyltype loc) : SingleAddrExpr(loc) {}

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};


#endif
