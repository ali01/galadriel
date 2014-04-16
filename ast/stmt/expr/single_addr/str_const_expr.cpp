#include "str_const_expr.h"

/* simone includes */
#include <simone/utility.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../../type/type.h"

StrConstExpr::StrConstExpr(yyltype loc, const string& _value) :
  SingleAddrExpr(loc), value_(_value) {}

Type::PtrConst
StrConstExpr::type() const {
  return Type::kString;
}
