#include "call_expr.h"

/* ast includes */
#include "../../../../identifier.h"

/* ast/decl includes */
#include "../../../../decl/fn_decl.h"

/* ast/type includes */
#include "../../../../type/type.h"

CallExpr::CallExpr(yyltype _loc,
                   Simone::Ptr<Identifier> _identifier,
                   Deque<Expr::Ptr>::Ptr _args) :
  SingleAddrExpr(_loc), identifier_(_identifier), actuals_(_args)
{
  assert(identifier_ != NULL && actuals_ != NULL);
}

Identifier::Ptr
CallExpr::identifier() {
  return identifier_;
}

Identifier::PtrConst
CallExpr::identifier() const {
  return identifier_;
}

CallExpr::const_reverse_actuals_iter
CallExpr::actualsReverseBegin() const {
  return actuals_->rbegin();
}

CallExpr::const_reverse_actuals_iter
CallExpr::actualsReverseEnd() const {
  return actuals_->rend();
}

Type::PtrConst
CallExpr::type() const {
  Type::PtrConst type = Type::kError;

  FnDecl::PtrConst fn_decl = fnDecl();
  if (fn_decl)
    type = fn_decl->returnType();

  return type;
}

Location::Ptr
CallExpr::fnLocation() const {
  return fn_location_;
}

void
CallExpr::fnLocationIs(Location::Ptr _loc) {
  fn_location_ = _loc;
}
