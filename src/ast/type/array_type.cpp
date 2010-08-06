#include "array_type.h"

/* simone includes */
#include <simone/utility.h>

ArrayType::ArrayType(yyltype loc, Type::Ptr et) : Type(loc), elem_type_(et) {
  assert(et != NULL);
  eq_functor_ = ArrayTypeEqualityFunctor::ArrayTypeEqualityFunctorNew(this);
  subsume_functor_ = ArrayTypeSubsumeFunctor::ArrayTypeSubsumeFunctorNew(this);
}



ArrayType::ArrayTypeEqualityFunctor::ArrayTypeEqualityFunctor(ArrayType::Ptr t):
  TypeEqualityFunctor(t) {}


void
ArrayType::ArrayTypeEqualityFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (other == Type::kError) {
    equal_ = true;
  } else {
    equal_ = false;
  }
}

void
ArrayType::ArrayTypeEqualityFunctor::operator()(ArrayType *_o) {
  ArrayType::PtrConst at = Ptr::st_cast<const ArrayType>(type_);
  equal_ = *at->elemType() == *_o->elemType();
}



ArrayType::ArrayTypeSubsumeFunctor::ArrayTypeSubsumeFunctor(ArrayType::Ptr _t) :
  TypeSubsumeFunctor(_t) {}

void
ArrayType::ArrayTypeSubsumeFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (other == Type::kError || other == Type::kNull) {
    subsumes_other_ = true;
  } else {
    subsumes_other_ = false;
  }
}


void
ArrayType::ArrayTypeSubsumeFunctor::operator()(ArrayType *_o) {
  /* static downcasting of this_type_ from Type to ArrayType */
  ArrayType::PtrConst this_at = Ptr::st_cast<const ArrayType>(this_type_);
  subsumes_other_ = *this_at->elemType() == *_o->elemType();
}
