#include "call_expr.h"

/* ast includes */
#include "../../../identifier.h"

/* ast/decl includes */
#include "../../../decl/fn_decl.h"

/* ast/type includes */
#include "../../../type/type.h"

CallExpr::CallExpr(yyltype _loc,
                   Simone::Ptr<Identifier> _function,
                   Deque<Expr::Ptr>::Ptr _args) :
  Expr(_loc), function_(_function), actuals_(_args)
{
  assert(function_ != NULL && actuals_ != NULL);
}

Identifier::Ptr
CallExpr::function() {
  return function_;
}

Identifier::PtrConst
CallExpr::function() const {
  return function_;
}


Type::PtrConst
CallExpr::type() const {
  Type::PtrConst type = Type::kError;

  FnDecl::PtrConst fn_decl = fnDecl();
  if (fn_decl)
    type = fn_decl->returnType();

  return type;
}
