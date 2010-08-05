#include "int_const_expr.h"

/* ast/type includes */
#include "../../../type/type.h"

Type::PtrConst
IntConstExpr::type() const {
  return Type::kInt;
}
