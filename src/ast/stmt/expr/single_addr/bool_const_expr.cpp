#include "bool_const_expr.h"

#include "../../../type/type.h"

Type::PtrConst
BoolConstExpr::type() const {
  return Type::kBool;
}
