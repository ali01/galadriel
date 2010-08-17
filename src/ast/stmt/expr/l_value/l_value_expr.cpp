#include "l_value_expr.h"

/* simone includes */
#include <simone/utility.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* project includes */
#include <lex_location.h>
#include <scope/scope.h>

/* ast/decl includes */
#include "../../../decl/var_decl.h"

/* ast/decl/object includes */
#include "../../../decl/object/class_decl.h"

/* ast/type/named includes */
#include "../../../type/named_type.h"

/* ast/stmt/expr includes */
#include "../expr.h"
#include "../this_expr.h"


LValueExpr::LValueExpr(yyltype loc) :
  Expr(loc) {}

Type::PtrConst
LValueExpr::type() const {
  Type::PtrConst type = Type::kError;

  VarDecl::PtrConst var_decl = varDecl();
  if(var_decl)
    type = var_decl->type();

  return type;
}


Location::Ptr
LValueExpr::location() const {
  return location_;
}

void
LValueExpr::locationIs(Location::Ptr _loc) {
  location_ = _loc;
}

Location::Ptr
LValueExpr::auxLocation() const {
  return aux_loc_;
}

void
LValueExpr::auxLocationIs(Location::Ptr _loc) {
  aux_loc_ = _loc;
}
