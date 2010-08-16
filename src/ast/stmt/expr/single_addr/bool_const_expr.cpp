#include "bool_const_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
BoolConstExpr::type() const {
  return Type::kBool;
}
