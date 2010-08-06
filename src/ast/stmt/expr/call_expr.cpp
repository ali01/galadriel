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

/* ast/decl includes */
#include "../../decl/fn_decl.h"
#include "../../decl/object/object_decl.h"

/* ast/type includes */
#include "../../type/type.h"
#include "../../type/named_type.h"
#include "../../type/array_type.h"

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
  base_decl_functor_ = BaseDeclFunctor::BaseDeclFunctorNew(this);
}


Identifier::Ptr
CallExpr::function() {
  return function_;
}

Identifier::PtrConst
CallExpr::function() const {
  return function_;
}

ObjectDecl::PtrConst
CallExpr::baseDecl() const {
  ObjectDecl::PtrConst base_decl = NULL;

  if (base_) {
    Type::PtrConst base_type_const = base_->type();
    Type::Ptr base_type = const_cast<Type*>(base_type_const.ptr());
    base_type->apply(base_decl_functor_);
    base_decl = base_decl_functor_->baseDecl();

  } else {
    base_decl = enclosingClass(); // TODO: what about interfaces?
  }

  return base_decl;
}

FnDecl::PtrConst
CallExpr::fnDecl() const {
  FnDecl::PtrConst fn_decl = NULL;

  Scope::PtrConst scope;
  ObjectDecl::PtrConst base_decl = this->baseDecl();

  if (base_decl) {
    scope = base_decl->scope();
    fn_decl = scope->fnDecl(function_, false);
  } else {
    scope = this->scope();
    fn_decl = scope->fnDecl(function_);
  }

  return fn_decl;
}

Type::PtrConst
CallExpr::type() const {
  Type::PtrConst type = Type::kError;

  FnDecl::PtrConst fn_decl = fnDecl();
  if (fn_decl)
    type = fn_decl->returnType();

  return type;
}

ObjectDecl::Ptr
CallExpr::BaseDeclFunctor::baseDecl() const {
  return base_decl_;
}


void
CallExpr::BaseDeclFunctor::operator()(NamedType *_type) {
  base_decl_ = _type->objectDecl();
}

void
CallExpr::BaseDeclFunctor::operator()(ArrayType *_type) {
  base_decl_ = _type->builtinClassDecl();
}
