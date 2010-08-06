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

Identifier::PtrConst
NamedType::identifier() const {
  return id_;
}

Identifier::Ptr
NamedType::identifier() {
  return id_;
}


ClassDecl::Ptr
NamedType::classDecl() {
  Scope::Ptr scope = this->scope();
  Identifier::PtrConst id = this->identifier();
  return scope->classDecl(id);
}

ClassDecl::PtrConst
NamedType::classDecl() const {
  NamedType::Ptr me = const_cast<NamedType*>(this);
  return me->classDecl();
}


NamedType::NamedTypeEqualityFunctor::NamedTypeEqualityFunctor(NamedType::Ptr t):
  TypeEqualityFunctor(t) {}


void
NamedType::NamedTypeEqualityFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (other == Type::kError) {
    equal_ = true;
  } else {
    equal_ = false;
  }
}

void
NamedType::NamedTypeEqualityFunctor::operator()(NamedType *_o) {
  NamedType::PtrConst nt = Ptr::st_cast<const NamedType>(type_);
  equal_ = *nt->identifier() == *_o->identifier();
}



NamedType::NamedTypeSubsumeFunctor::
NamedTypeSubsumeFunctor(NamedType::Ptr _t) : TypeSubsumeFunctor(_t) {}

void
NamedType::NamedTypeSubsumeFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (other == Type::kError || other == Type::kNull) {
    subsumes_other_ = true;
  } else {
    subsumes_other_ = false;
  }
}

void
NamedType::NamedTypeSubsumeFunctor::operator()(NamedType *_o) {
  if (*this_type_ == *_o) {
    subsumes_other_ = true;
  } else {
    /* static downcasting this_type_ from Type to NamedType */
    NamedType::PtrConst this_nt = Ptr::st_cast<const NamedType>(this_type_);
    ClassDecl::PtrConst class_decl = _o->classDecl();
    if (class_decl != NULL) {
      subsumes_other_ = class_decl->subsumersContain(this_nt);
    } else {
      subsumes_other_ = false;
    }
  }
}
