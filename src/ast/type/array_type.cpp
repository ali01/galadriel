#include "array_type.h"

/* simone includes */
#include <simone/utility.h>

ArrayType::ArrayType(yyltype loc, Type *et) : Type(loc) {
  assert(et != NULL);
}
