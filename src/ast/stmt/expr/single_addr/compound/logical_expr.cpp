#include "logical_expr.h"

#include "../../../../type/type.h"

Type::PtrConst
LogicalExpr::type() const {
  return Type::kBool;
}
