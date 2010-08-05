#include "type.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* Class constants
 * ---------------
 * These are public constants for the built-in base types (int, double, etc.)
 * They can be accessed with the syntax Type::intType. This allows you to
 * directly access them and share the built-in types where needed rather that
 * creates lots of copies.
 */

Type::PtrConst Type::kInt    = Type::TypeNew("int");
Type::PtrConst Type::kDouble = Type::TypeNew("double");
Type::PtrConst Type::kBool   = Type::TypeNew("bool");
Type::PtrConst Type::kString = Type::TypeNew("string");
Type::PtrConst Type::kVoid   = Type::TypeNew("void");
Type::PtrConst Type::kNull   = Type::TypeNew("null");
Type::PtrConst Type::kError  = Type::TypeNew("error");

/* protected constructors */
Type::Type(yyltype loc, const string& str) : 
  Node(loc), type_name_(str)
{
  eq_functor_ = TypeEqualityFunctor::TypeEqualityFunctorNew(this);
}

Type::Type(yyltype loc) : Node(loc) {
  eq_functor_ = TypeEqualityFunctor::TypeEqualityFunctorNew(this);
}

/* private constructor */
Type::Type(const string& str) : Node(), type_name_(str) {
  eq_functor_ = TypeEqualityFunctor::TypeEqualityFunctorNew(this);
}

bool
Type::operator==(const Type& _o) const {
  /* operator== is logically const;
     eq_functor_ implemented in type.h doesn't modify the object */
  Type &o_mutable = const_cast<Type&>(_o);

  o_mutable.apply(eq_functor_);
  return eq_functor_->equal();
}


ostream&
operator<<(ostream& out, Type *t) {
  out << t->name();
  return out;
}
