#ifndef STRING_CONSTANT_H_5V21HZS6
#define STRING_CONSTANT_H_5V21HZS6

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"

/* forward declarations */
class Type;

class StrConstExpr : public SingleAddrExpr {
public:
  typedef Simone::Ptr<const StrConstExpr> PtrConst;
  typedef Simone::Ptr<StrConstExpr> Ptr;

  static Ptr StrConstExprNew(yyltype loc, const char *v) {
    return new StrConstExpr(loc, v);
  }

  StrConstExpr(yyltype loc, const char *v);

  Simone::Ptr<const Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  char *value;
};

#endif
