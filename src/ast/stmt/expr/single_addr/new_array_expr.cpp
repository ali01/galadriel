#include "new_array_expr.h"

/* simone includes */
#include <simone/utility.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/stmt/expr includes */
#include "../expr.h"

/* ast/type includes */
#include "../../../type/type.h"
#include "../../../type/array_type.h"

NewArrayExpr::NewArrayExpr(yyltype loc, Expr::Ptr sz, Type::Ptr _elem_type) :
  SingleAddrExpr(loc), size_(sz)
{
  assert(sz != NULL && _elem_type != NULL);
  type_ = ArrayType::ArrayTypeNew(loc, _elem_type);
}

ArrayType::PtrConst
NewArrayExpr::arrayType() const {
  return type_;
}

ArrayType::Ptr
NewArrayExpr::arrayType() {
  return type_;
}

Type::PtrConst
NewArrayExpr::type() const {
  return type_;
}

Location::PtrConst
NewArrayExpr::auxLocation() const {
  return aux_loc_;
}

void
NewArrayExpr::auxLocationIs(Location::PtrConst _loc) {
  aux_loc_ = _loc;
}
