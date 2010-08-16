#include "null_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/type includes */
#include "../../type/type.h"

Type::PtrConst
NullExpr::type() const {
  return Type::kNull;
}

Location::PtrConst
NullExpr::location() const {
  return NULL;
}
