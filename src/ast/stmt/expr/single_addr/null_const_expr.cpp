#include "null_const_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
NullConstExpr::type() const {
  return Type::kNull;
}
