#include "call_expr.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <lex_loc.h>
#include <scope.h>

/* ast includes */
#include "../../identifier.h"

/* ast/type includes */
#include "../../type/type.h"

/* ast/stmt/expr includes */
#include "expr.h"

CallExpr::CallExpr(yyltype _loc,
                   Expr::Ptr _base,
                   Identifier::Ptr _function,
                   Deque<Expr::Ptr>::Ptr _args) :
  Expr(_loc), base_(_base), function_(_function), actuals_(_args)
{
  /* base can be null if implicit */
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
  Type::PtrConst type;
  FnDecl::PtrConst fn_decl;
  Scope::PtrConst scope = this->scope();
  // TODO: finish
  if (base_) {
    // NamedType::PtrConst base_type = base_->type();
    // ClassDecl::PtrConst class_decl = 
  } else {
    fn_decl = scope->fnDecl(function_);
  }

  if (fn_decl) {
    type = fn_decl->returnType();
  } else {
    type = Type::kError;
  }

  return type;
}
