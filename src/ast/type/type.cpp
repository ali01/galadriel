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

Type *Type::intType     = new Type("int");
Type *Type::doubleType  = new Type("double");
Type *Type::boolType    = new Type("bool");
Type *Type::stringType  = new Type("string");

Type::Type(yyltype loc, const char *n) : Node(loc), typeName(strdup(n)) {
  assert(typeName);
}
