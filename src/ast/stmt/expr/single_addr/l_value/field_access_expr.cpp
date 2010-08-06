#include "field_access_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <scope.h>

/* ast includes */
#include "../../../../identifier.h"

/* ast/decl includes */
#include "../../../../decl/var_decl.h"

/* ast/decl/object includes */
#include "../../../../decl/class_decl.h"

/* ast/type/named includes */
#include "../../../../type/named_type.h"

/* ast/stmt/expr includes */
#include "../../expr.h"

/* ast/stmt/expr/single_addr/l_value includes */
#include "l_value_expr.h"


FieldAccessExpr::FieldAccessExpr(Expr::Ptr b, Identifier::Ptr f) :
  LValueExpr(b != NULL ?  Join(b->lexLoc(), f->lexLoc()) : *f->lexLoc()),
  base_(b), field_(f)
{
  /* b can be null (just means no explicit base) */
  assert(field_ != NULL);
}

Identifier::Ptr
FieldAccessExpr::field() {
  return field_;
}

Identifier::PtrConst
FieldAccessExpr::field() const {
  return field_;
}

Type::PtrConst
FieldAccessExpr::type() const {
  Type::PtrConst type = Type::kError;
  Scope::PtrConst scope;
  VarDecl::PtrConst var_decl = NULL;
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
    var_decl = scope->varDecl(field_, false);
  } else {
    scope = this->scope();
    var_decl = scope->varDecl(field_);
  }

  if(var_decl)
    type = var_decl->type();

  return type;
}
