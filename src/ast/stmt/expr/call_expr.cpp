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
  Type::PtrConst type = Type::kError;
  Scope::PtrConst scope;
  FnDecl::PtrConst fn_decl = NULL;
  ClassDecl::PtrConst base_decl = NULL;

  if (base_) {
    NamedType::PtrConst base_type;
    base_type = dynamic_cast<const NamedType*>(base_->type().ptr());
    if (base_type)
      base_decl = base_type->classDecl();

  } else {
    base_decl = enclosingClass();
  }

  if (base_decl) {
    scope = base_decl->scope();
    fn_decl = scope->fnDecl(function_, false);
  } else {
    scope = this->scope();
    fn_decl = scope->fnDecl(function_);
  }

  if (fn_decl)
    type = fn_decl->returnType();

  return type;
}
