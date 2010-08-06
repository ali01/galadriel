#include "null_expr.h"

#include "../../type/type.h"

Type::PtrConst
NullExpr::type() const {
  return Type::kNull;
}
