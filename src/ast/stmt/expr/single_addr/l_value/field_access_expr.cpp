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
#include "../../../../decl/object/class_decl.h"

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
  assert(base_ != NULL && field_ != NULL);
}

Identifier::Ptr
FieldAccessExpr::field() {
  return field_;
}

Identifier::PtrConst
FieldAccessExpr::field() const {
  return field_;
}

ClassDecl::PtrConst
FieldAccessExpr::baseDecl() const {
  ClassDecl::PtrConst base_decl = NULL;

  Type::PtrConst base_type = base_->type();
  if (base_type->isNamedType()) {
    NamedType::PtrConst named_type = Ptr::st_cast<const NamedType>(base_type);
    base_decl = named_type->classDecl();
  }

  return base_decl;
}

VarDecl::PtrConst
FieldAccessExpr::varDecl() const {
  VarDecl::PtrConst var_decl = NULL;
  
  ClassDecl::PtrConst base_decl = baseDecl();
  if (base_decl) {
    Scope::PtrConst scope = base_decl->scope();
    var_decl = scope->varDecl(field_, false);
  }

  return var_decl;
}

Type::PtrConst
FieldAccessExpr::type() const {
  Type::PtrConst type = Type::kError;

  VarDecl::PtrConst var_decl = varDecl();
  if(var_decl)
    type = var_decl->type();

  return type;
}
