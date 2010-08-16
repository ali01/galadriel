#include "read_line_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
ReadLineExpr::type() const {
  return Type::kString;
}
