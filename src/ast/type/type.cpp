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

Type::Ptr Type::kInt    = Type::TypeNew("int");
Type::Ptr Type::kDouble = Type::TypeNew("double");
Type::Ptr Type::kBool   = Type::TypeNew("bool");
Type::Ptr Type::kString = Type::TypeNew("string");
Type::Ptr Type::kVoid   = Type::TypeNew("void");
Type::Ptr Type::kNull   = Type::TypeNew("null");
Type::Ptr Type::kError  = Type::TypeNew("error");

ostream&
operator<<(ostream& out, Type *t) {
  out << t->name();
  return out;
}
