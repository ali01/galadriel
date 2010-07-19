#include "str_const_expr.h"

/* simone includes */
#include <simone/utility.h>

StrConstExpr::StrConstExpr(yyltype loc, const char *val) :
  SingleAddrExpr(loc)
{
  assert(val != NULL);
  value = strdup(val);
}
