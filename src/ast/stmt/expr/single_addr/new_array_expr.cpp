#include "new_array_expr.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../expr.h"

/* ast/type includes */
#include "../../../type/type.h"
#include "../../../type/array_type.h"

// TODO: consider value of type_ ~ new ArrayType(loc, et);
NewArrayExpr::NewArrayExpr(yyltype loc, Expr::Ptr sz, Type::Ptr et) :
  SingleAddrExpr(loc), size_(sz), elem_type_(et)
{
  assert(sz != NULL && et != NULL);
  type_ = ArrayType::ArrayTypeNew(loc, elem_type_);
}


Type::PtrConst
NewArrayExpr::elemType() const {
  return elem_type_;
}

Type::Ptr
NewArrayExpr::elemType() {
  return elem_type_;
}

Type::PtrConst
NewArrayExpr::type() const {
  return type_;
}
