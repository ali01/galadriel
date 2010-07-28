/* File: type.h
 * ----------------
 * In our parse tree, Type nodes are used to represent and
 * store type information. The base Type class is used
 * for built-in types, the NamedType for classes and interfaces,
 * and the ArrayType for arrays of other types.
 */

#ifndef TYPE_H_Y3MLXI9M
#define TYPE_H_Y3MLXI9M

/* stl includes */
#include <string>

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "../node.h"

class Type : public Node  {
public:
  typedef Simone::Ptr<const Type> PtrConst;
  typedef Simone::Ptr<Type> Ptr;

  static Type::Ptr kInt, kDouble, kBool, kString,
                   kVoid, kNull, kError;

  static Ptr TypeNew(const string& str) {
    return new Type(str);
  }

  const string& name() { return type_name_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Type(yyltype loc) : Node(loc) {}
  Type(yyltype loc, const string& str) : Node(loc), type_name_(str) {}
  Type(const string& str) : Node(), type_name_(str) {}

  /* data members */
  const string type_name_;
};

/* forward declarations */
ostream& operator<<(ostream& out, Type *t);

#endif
