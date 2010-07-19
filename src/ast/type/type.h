/* File: type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 */

#ifndef TYPE_H_Y3MLXI9M
#define TYPE_H_Y3MLXI9M

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "../node.h"

#define kIntType      Type::intType
#define kDoubleType   Type::doubleType
#define kBoolType     Type::boolType
#define kStringType   Type::stringType

class Type : public Node  {
public:
  static Type *intType, *doubleType, *boolType, *stringType;

  Type(yyltype loc) : Node(loc) {}
  Type(const char *str) : Node(), typeName(strdup(str)) { assert(typeName); }
  Type(yyltype loc, const char *str);

  const char *name() { return typeName; }

  friend ostream& operator<<(ostream& out, Type *t);

protected:
  /* data members */
  char *typeName;
};

#endif
