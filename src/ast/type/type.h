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

/* forward declarations */
class NamedType;

class Type : public Node  {
public:
  typedef Simone::Ptr<const Type> PtrConst;
  typedef Simone::Ptr<Type> Ptr;

  static Type::PtrConst kInt, kDouble, kBool, kString,
                   kVoid, kNull, kError;

  static Ptr TypeNew(const string& str) {
    return new Type(str);
  }

  const string& name() { return type_name_; }

  /* overloaded operators */
  bool operator==(const Type& _o) const;
  bool operator!=(const Type& _o) const { return !(*this == _o); }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  class TypeEqualityFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const TypeEqualityFunctor> PtrConst;
      typedef Simone::Ptr<TypeEqualityFunctor> Ptr;

      static Ptr TypeEqualityFunctorNew(Type::Ptr _type) {
        return new TypeEqualityFunctor(_type);
      }

      void operator()(Type *_o) { equal_ = type_.ptr() == _o; }
      void operator()(NamedType *_o) { equal_ = false; }
      void operator()(ArrayType *_o) { equal_ = false; }

      bool equal() const { return equal_; }

    protected:
      TypeEqualityFunctor(Type::Ptr _type) : type_(_type), equal_(false) {}

      /* data members */
      Type::Ptr type_;
      bool equal_;
  };

  /* constructor to be used by derived classes */
  Type(yyltype loc, const string& str);
  Type(yyltype loc);

  /* data members */
  const string type_name_;
  TypeEqualityFunctor::Ptr eq_functor_;

private:
  Type(const string& str);
};

/* forward declarations */
ostream& operator<<(ostream& out, Type *t);

#endif
