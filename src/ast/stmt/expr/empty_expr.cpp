#include "empty_expr.h"

#include "../../type/type.h"

Type::PtrConst
EmptyExpr::type() const {
  assert(false); // TODO
  return NULL;
}