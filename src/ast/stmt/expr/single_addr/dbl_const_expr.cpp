#include "dbl_const_expr.h"

#include "../../../type/type.h"

Type::PtrConst
DblConstExpr::type() const {
  return Type::kDouble;
}
