#include "type.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_location.h>

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type::Ptr Type::kInt    = Type::TypeNew("int");
Type::Ptr Type::kDouble = Type::TypeNew("double");
Type::Ptr Type::kBool   = Type::TypeNew("bool");
Type::Ptr Type::kString = Type::TypeNew("string");
Type::Ptr Type::kVoid   = Type::TypeNew("void");
Type::Ptr Type::kNull   = Type::TypeNew("null");
Type::Ptr Type::kError  = Type::TypeNew("error");

/* protected constructors */
Type::Type(yyltype loc, const string& str) : 
  Node(loc), type_name_(str)
{
  eq_functor_ = TypeEqualityFunctor::TypeEqualityFunctorNew(this);
  subsume_functor_ = TypeSubsumeFunctor::TypeSubsumeFunctorNew(this);
}

/* private constructor */
Type::Type(const string& str) : Node(), type_name_(str) {
  eq_functor_ = TypeEqualityFunctor::TypeEqualityFunctorNew(this);
  subsume_functor_ = TypeSubsumeFunctor::TypeSubsumeFunctorNew(this);
}

bool
Type::subsumes(const Type::PtrConst& _o) const {
  /* subsumes function is logically const;
     subsume_functor_, implemented in type.h, doesn't modify the object */
  Type::Ptr o_mutable = const_cast<Type*>(_o.ptr());

  subsume_functor_(o_mutable);
  return subsume_functor_->subsumesOther();
}

bool
Type::operator==(const Type& _o) const {
  /* operator== is logically const;
     eq_functor_, implemented in type.h, doesn't modify the object */
  Type &o_mutable = const_cast<Type&>(_o);

  eq_functor_(&o_mutable);
  return eq_functor_->equal();
}

void
Type::TypeEqualityFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (type_ == Type::kError || other == Type::kError) {
    equal_ = true;
  } else {
    equal_ = type_.ptr() == _o;
  }
}

void
Type::TypeEqualityFunctor::operator()(NamedType *_o) {
  if (type_ == Type::kError) {
    equal_ = true;
  } else {
    equal_ = false;
  }
}

void
Type::TypeEqualityFunctor::operator()(ArrayType *_o) {
  if (type_ == Type::kError) {
    equal_ = true;
  } else {
    equal_ = false;
  }
}


void
Type::TypeSubsumeFunctor::operator()(Type *_o) {
  Type::Ptr other = _o;
  if (this_type_ == Type::kError || other == Type::kError) {
    subsumes_other_ = true;
  } else {
    subsumes_other_ = *this_type_ == *_o;
  }
}

void
Type::TypeSubsumeFunctor::operator()(NamedType *) {
  if (this_type_ == Type::kError) {
    subsumes_other_ = true;
  } else {
    subsumes_other_ = false;
  }
}

void
Type::TypeSubsumeFunctor::operator()(ArrayType *) {
  if (this_type_ == Type::kError) {
    subsumes_other_ = true;
  } else {
    subsumes_other_ = false;
  }
}

ostream&
operator<<(ostream& out, const Type& t) {
  out << t.name();
  return out;
}
