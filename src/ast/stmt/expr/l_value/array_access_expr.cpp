#include "array_access_expr.h"

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/stmt/expr includes */
#include "../expr.h"

/* ast/type includes */
#include "../../../type/type.h"
#include "../../../type/array_type.h"


ArrayAccessExpr::ArrayAccessExpr(yyltype loc, Expr::Ptr b, Expr::Ptr s) :
  LValueExpr(loc), base_(b), subscript_(s) {}

Type::PtrConst
ArrayAccessExpr::type() const {
  Type::PtrConst elem_type, base_type;

  base_type = base_->type();
  if (base_type->isArrayType()) {
    ArrayType::PtrConst array_type = Ptr::st_cast<const ArrayType>(base_type);
    elem_type = array_type->elemType();
  } else {
    elem_type = Type::kError;
  }

  return elem_type;
}

Location::Ptr
ArrayAccessExpr::location() const {
  return location_;
}

void
ArrayAccessExpr::locationIs(Location::Ptr _loc) {
  location_ = _loc;
}

TmpLocation::Ptr
ArrayAccessExpr::auxLocation() const {
  return aux_loc_;
}

void
ArrayAccessExpr::auxLocationIs(TmpLocation::Ptr _loc) {
  aux_loc_ = _loc;
}
