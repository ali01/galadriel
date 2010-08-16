#include "int_const_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
IntConstExpr::type() const {
  return Type::kInt;
}
