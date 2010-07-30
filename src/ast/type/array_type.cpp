#include "array_type.h"

/* simone includes */
#include <simone/utility.h>

// TODO: assign data member
ArrayType::ArrayType(yyltype loc, Type::Ptr et) : Type(loc), elem_type_(et) {
  assert(et != NULL);
  eq_functor_ = ArrayTypeEqualityFunctor::ArrayTypeEqualityFunctorNew(this);
}

ArrayType::ArrayTypeEqualityFunctor::ArrayTypeEqualityFunctor(ArrayType::Ptr t):
  TypeEqualityFunctor(t) {}

void
ArrayType::ArrayTypeEqualityFunctor::operator()(ArrayType *_o) {
  ArrayType::PtrConst at = Ptr::st_cast<const ArrayType>(type_);
  equal_ = *at->elemType() == *_o->elemType();
}