#include "field_access_expr.h"

/* simone includes */
#include <simone/utility.h>

/* code_generator includes */
#include <code_generator/location_includes.h>

/* project includes */
#include <lex_location.h>
#include <scope/scope.h>

/* ast includes */
#include "../../../identifier.h"

/* ast/decl includes */
#include "../../../decl/var_decl.h"

/* ast/decl/object includes */
#include "../../../decl/object/class_decl.h"

/* ast/type/named includes */
#include "../../../type/named_type.h"

/* ast/stmt/expr includes */
#include "../expr.h"
#include "../this_expr.h"


FieldAccessExpr::FieldAccessExpr(Expr::Ptr b, Identifier::Ptr f) :
  LValueExpr(Join(b->lexLoc(), f->lexLoc())), base_(b), identifier_(f)
{
  assert(base_ != NULL && identifier_);
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
    var_decl = scope->varDecl(identifier_, false);
  }

  return var_decl;
}

Identifier::Ptr
FieldAccessExpr::identifier() {
  return identifier_;
}

Identifier::PtrConst
FieldAccessExpr::identifier() const {
  return identifier_;
}
