#include "method_call_expr.h"

/* project includes */
#include <scope/scope.h>

/* code_generator includes */
#include <code_generator/location/location.h>

/* ast includes */
#include "../../../identifier.h"

/* ast/decl includes */
#include "../../../decl/fn_decl.h"
#include "../../../decl/object/object_decl.h"

/* ast/type includes */
#include "../../../type/named_type.h"
#include "../../../type/array_type.h"

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

Location::Ptr
MethodCallExpr::location() {
  return NULL;
}
