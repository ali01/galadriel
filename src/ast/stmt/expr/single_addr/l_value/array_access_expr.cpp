#include "array_access_expr.h"

/* ast/stmt/expr includes */
#include "../../expr.h"

/* ast/type includes */
#include "../../../../type/type.h"
#include "../../../../type/array_type.h"


ArrayAccessExpr::ArrayAccessExpr(yyltype loc, Expr::Ptr b, Expr::Ptr s) :
  LValueExpr(loc), base_(b), subscript_(s) {}

Type::PtrConst
ArrayAccessExpr::type() const {
  Type::PtrConst elem_type;

  ArrayType::PtrConst array_type;
  array_type = dynamic_cast<const ArrayType*>(base_->type().ptr());

  if (array_type != NULL) {
    elem_type = array_type->elemType();
  } else {
    elem_type = Type::kError;
  }

  // TODO: think about subscript requirements

  return elem_type;
}
