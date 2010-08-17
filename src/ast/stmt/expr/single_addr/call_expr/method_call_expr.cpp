#include "method_call_expr.h"

/* project includes */
#include <scope/scope.h>

/* ast includes */
#include "../../../../identifier.h"

/* ast/decl includes */
#include "../../../../decl/fn_decl.h"
#include "../../../../decl/object/object_decl.h"

/* ast/type includes */
#include "../../../../type/named_type.h"
#include "../../../../type/array_type.h"

/* ast/expr includes */
#include "../../this_expr.h"

/* local includes */
#include "function_call_expr.h"

MethodCallExpr::Ptr
MethodCallExpr::MethodCallExprNew(FunctionCallExpr::Ptr _fn_call) {
  Identifier::Ptr id = _fn_call->identifier();
  Deque<Expr::Ptr>::Ptr actuals = _fn_call->actuals_;

  ThisExpr::Ptr base = ThisExpr::ThisExprNew(_fn_call->parent(), 
                                             _fn_call->scope());

  MethodCallExpr::Ptr ex;
  ex = new MethodCallExpr(*_fn_call->lexLoc(), base, id, actuals);
  ex->locationIs(_fn_call->location());
  ex->auxLocationIs(_fn_call->auxLocation());
  ex->parentIs(_fn_call->parent());
  ex->scopeIs(_fn_call->scope());

  return ex;
}

MethodCallExpr::MethodCallExpr(yyltype _loc,
                               Expr::Ptr _base,
                               Identifier::Ptr _identifier,
                               Deque<Expr::Ptr>::Ptr _args) :
  CallExpr(_loc, _identifier, _args), base_(_base)
{
  assert(base_);
  base_decl_functor_ = BaseDeclFunctor::BaseDeclFunctorNew(this);
}


ObjectDecl::PtrConst
MethodCallExpr::baseDecl() const {
  Type::PtrConst base_type_const = base_->type();
  Type::Ptr base_type = const_cast<Type*>(base_type_const.ptr());
  base_decl_functor_(base_type);
  return base_decl_functor_->baseDecl();
}


FnDecl::PtrConst
MethodCallExpr::fnDecl() const {
  FnDecl::PtrConst fn_decl = NULL;

  ObjectDecl::PtrConst base_decl = baseDecl();
  if (base_decl) {
    Scope::PtrConst scope = base_decl->scope();
    fn_decl = scope->fnDecl(identifier_, false);
  }

  return fn_decl;
}

int
MethodCallExpr::vTableOffset() const {
  int off = 0;

  ObjectDecl::PtrConst base_decl = baseDecl();
  if (base_decl) {
    FnDecl::PtrConst fn_decl;
    Scope::PtrConst scope = base_decl->scope();
    Scope::const_fn_decl_iter it = scope->fnDeclsBegin();
    for (int i = 0; it != scope->fnDeclsEnd(); ++it, ++i) {
      fn_decl = it->second;

      if (*fn_decl->identifier() == *this->identifier()) {
        off = i;
        break;
      }
    }
  }

  return off;
}


ObjectDecl::Ptr
MethodCallExpr::BaseDeclFunctor::baseDecl() const {
  return base_decl_;
}

void
MethodCallExpr::BaseDeclFunctor::operator()(NamedType *_type) {
  base_decl_ = _type->objectDecl();
}


void
MethodCallExpr::BaseDeclFunctor::operator()(ArrayType *_type) {
  base_decl_ = _type->builtinClassDecl();
}
