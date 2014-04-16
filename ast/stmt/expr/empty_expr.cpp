#include "empty_expr.h"

#include "../../type/type.h"

Type::PtrConst
EmptyExpr::type() const {
  return Type::kVoid;
}

Location::Ptr
EmptyExpr::location() const {
  return NULL;
}
