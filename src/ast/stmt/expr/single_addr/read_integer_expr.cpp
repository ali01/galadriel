#include "read_integer_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
ReadIntegerExpr::type() const {
  return Type::kInt;
}
