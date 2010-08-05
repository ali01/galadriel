#include "named_type.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <scope.h>

/* ast/decl includes */
#include "../decl/class_decl.h"

NamedType::NamedType(Identifier::Ptr _id) :
  Type(*_id->lexLoc(), _id->name()), id_(_id)
{
  assert(id_ != NULL);
  eq_functor_ = NamedTypeEqualityFunctor::NamedTypeEqualityFunctorNew(this);
  subsume_functor_ = NamedTypeSubsumeFunctor::NamedTypeSubsumeFunctorNew(this);
}

Identifier::Ptr
NamedType::identifier() const {
  return id_;
}



NamedType::NamedTypeEqualityFunctor::NamedTypeEqualityFunctor(NamedType::Ptr t):
  TypeEqualityFunctor(t) {}

void
NamedType::NamedTypeEqualityFunctor::operator()(NamedType *_o) {
  NamedType::PtrConst nt = Ptr::st_cast<const NamedType>(type_);
  equal_ = *nt->identifier() == *_o->identifier();
}



NamedType::NamedTypeSubsumeFunctor::
NamedTypeSubsumeFunctor(NamedType::Ptr _t) : TypeSubsumeFunctor(_t) {}

void
NamedType::NamedTypeSubsumeFunctor::operator()(NamedType *_o) {
  if (*this_type_ == *_o) {
    subsumes_other_ = true;
  } else {
    /* static downcasting this_type_ from Type to NamedType */
    NamedType::PtrConst this_nt = Ptr::st_cast<const NamedType>(this_type_);

    /* obtaining type identifier using accessor */
    Identifier::PtrConst this_id = this_nt->identifier();

    /* finding the named type's class declaration */
    Scope::PtrConst scope = this_nt->scope();
    ClassDecl::PtrConst class_decl = scope->classDecl(this_id);

    if (class_decl != NULL) {
      subsumes_other_ = class_decl->subsumersContain(_o);
    } else {
      subsumes_other_ = false;
    }
  }
}
