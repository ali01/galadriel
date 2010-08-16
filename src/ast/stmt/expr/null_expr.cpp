#include "null_expr.h"

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast/type includes */
#include "../../type/type.h"

Type::PtrConst
NullExpr::type() const {
  return Type::kNull;
}

Location::Ptr
NullExpr::location() {
  return NULL;
}