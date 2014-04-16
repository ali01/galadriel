#ifndef STRING_CONSTANT_H_5V21HZS6
#define STRING_CONSTANT_H_5V21HZS6

/* stl includes */
#include <string>
using std::string;

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

  static Ptr StrConstExprNew(yyltype loc, const string& _value) {
    return new StrConstExpr(loc, _value);
  }

  StrConstExpr(yyltype loc, const string& _value);

  Simone::Ptr<const Type> type() const;
  const string& value() const { return value_; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  string value_;
};

#endif
