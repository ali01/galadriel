#include "read_line_expr.h"

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
ReadLineExpr::type() const {
  return Type::kString;
}
