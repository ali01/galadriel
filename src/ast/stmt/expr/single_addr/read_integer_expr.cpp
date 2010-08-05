#include "read_integer_expr.h"

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
ReadIntegerExpr::type() const {
  return Type::kInt;
}
