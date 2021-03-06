#ifndef READ_INTEGER_EXPR_H_DZTNBZO5
#define READ_INTEGER_EXPR_H_DZTNBZO5

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Location;
class Type;

class ReadIntegerExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const ReadIntegerExpr> PtrConst;
  typedef Simone::Ptr<ReadIntegerExpr> Ptr;

  static Ptr ReadIntegerExprNew(yyltype loc) {
    return new ReadIntegerExpr(loc);
  }

  ReadIntegerExpr(yyltype loc) : SingleAddrExpr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
