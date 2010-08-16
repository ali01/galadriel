#include "dbl_const_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
DblConstExpr::type() const {
  return Type::kDouble;
}
