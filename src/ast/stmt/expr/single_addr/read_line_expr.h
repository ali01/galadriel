#ifndef READ_LINE_EXPR_H_VCPJ04FG
#define READ_LINE_EXPR_H_VCPJ04FG

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Type;

class ReadLineExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const ReadLineExpr> PtrConst;
  typedef Simone::Ptr<ReadLineExpr> Ptr;

  static Ptr ReadLineExprNew(yyltype loc) {
    return new ReadLineExpr(loc);
  }

  ReadLineExpr(yyltype loc) : SingleAddrExpr(loc) {}

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
