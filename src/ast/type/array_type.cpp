#include "array_type.h"

/* simone includes */
#include <simone/utility.h>

// TODO: assign data member
ArrayType::ArrayType(yyltype loc, Type::Ptr et) : Type(loc) {
  assert(et != NULL);
}
