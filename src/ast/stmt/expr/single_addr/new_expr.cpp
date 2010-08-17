#include "new_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_location.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* ast/decl includes */
#include "../../../decl/object/class_decl.h"

/* ast/type/named includes */
#include "../../../type/named_type.h"

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"


NewExpr::NewExpr(yyltype loc, NamedType::Ptr class_type) :
  SingleAddrExpr(loc), type_(class_type)
{
  assert(type_ != NULL);
}

NamedType::PtrConst
NewExpr::objectType() const {
  return type_;
}

NamedType::Ptr
NewExpr::objectType() {
  return type_;
}

Location::PtrConst
NewExpr::sizeLocation() const {
  return size_loc_;
}

void
NewExpr::sizeLocationIs(Location::PtrConst _loc) {
  size_loc_ = _loc;
}

Location::PtrConst
NewExpr::vPtrLocation() const {
  return v_ptr_loc_;
}

void
NewExpr::vPtrLocationIs(Location::PtrConst _loc) {
  v_ptr_loc_ = _loc;
}

Type::PtrConst
NewExpr::type() const {
  return objectType();
}
