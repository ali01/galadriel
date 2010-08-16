#include "str_const_expr.h"

/* simone includes */
#include <simone/utility.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../../type/type.h"

StrConstExpr::StrConstExpr(yyltype loc, const char *val) :
  SingleAddrExpr(loc)
{
  assert(val != NULL);
  value = strdup(val);
}

Type::PtrConst
StrConstExpr::type() const {
  return Type::kString;
}
