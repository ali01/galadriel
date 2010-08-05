#include "null_const_expr.h"

#include "../../type/type.h"

Type::PtrConst
NullConstExpr::type() const {
  return Type::kNull;
}
