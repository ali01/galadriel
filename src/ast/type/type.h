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

  static Type::Ptr kInt, kDouble, kBool, kString,
                   kVoid, kNull, kError;

  static Ptr TypeNew(const string& str) {
    return new Type(str);
  }

  const string& name() const { return type_name_; }

  bool subsumes(const Type::PtrConst& _other) const;

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

      void operator()(Type *_o);
      void operator()(NamedType *_o);
      void operator()(ArrayType *_o);

      bool equal() const { return equal_; }

    protected:
      TypeEqualityFunctor(Type::Ptr _type) : type_(_type), equal_(false) {}

      /* data members */
      Type::Ptr type_;
      bool equal_;
  };

  class TypeSubsumeFunctor : public Node::Functor {
    public:
      typedef Simone::Ptr<const TypeSubsumeFunctor> PtrConst;
      typedef Simone::Ptr<TypeSubsumeFunctor> Ptr;

      static Ptr TypeSubsumeFunctorNew(Type::Ptr _this_type) {
        return new TypeSubsumeFunctor(_this_type);
      }

      void operator()(Type *_o);
      void operator()(NamedType *);
      void operator()(ArrayType *);

      bool subsumesOther() const { return subsumes_other_; }

    protected:
      TypeSubsumeFunctor(Type::Ptr _this_type) :
        this_type_(_this_type), subsumes_other_(false) {}
      
      /* data members */
      Type::Ptr this_type_;
      bool subsumes_other_;
  };

  /* constructor to be used by derived classes */
  Type(yyltype loc, const string& str);
  Type(yyltype loc);

  /* data members */
  const string type_name_;
  TypeEqualityFunctor::Ptr eq_functor_;
  TypeSubsumeFunctor::Ptr subsume_functor_;

private:
  Type(const string& str);
};

/* forward declarations */
ostream& operator<<(ostream& out, const Type& t);

#endif
