#include "function_call_expr.h"

/* project includes */
#include <scope.h>

/* ast/decl includes */
#include "../../../decl/fn_decl.h"

/* ast/type includes */
#include "../../../type/type.h"

FunctionCallExpr::FunctionCallExpr(yyltype _loc,
                                   Identifier::Ptr _identifier,
                                   Deque<Expr::Ptr>::Ptr _args) :
  CallExpr(_loc, _identifier, _args) {}

FnDecl::PtrConst
FunctionCallExpr::fnDecl() const {
  Scope::PtrConst scope = this->scope();
  return scope->fnDecl(identifier_);;
}
