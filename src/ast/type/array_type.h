#ifndef ARRAY_TYPE_H_J35FQYOQ
#define ARRAY_TYPE_H_J35FQYOQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/type includes */
#include "type.h"

class ArrayType : public Type {
public:
  typedef Simone::Ptr<const ArrayType> PtrConst;
  typedef Simone::Ptr<ArrayType> Ptr;

  static Ptr ArrayTypeNew(yyltype loc, Type::Ptr elem_type) {
    return new ArrayType(loc, elem_type);
  }

  ArrayType(yyltype loc, Type::Ptr elem_type);

  /* attribute member functions */
  Type::Ptr elemType() { return elem_type_; }
  Type::PtrConst elemType() const { return elem_type_; }

  Simone::Ptr<const ClassDecl> builtinClassDecl() const;
  Simone::Ptr<ClassDecl> builtinClassDecl();

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

  /* built-in array class identifier */
  static Simone::Ptr<Identifier> kArrayClassIdentifier;

  /* built-in array member functions */
  static Simone::Ptr<Identifier> kLengthFnIdentifier;

protected:
  class ArrayTypeEqualityFunctor : public Type::TypeEqualityFunctor {
    public:
      typedef Simone::Ptr<const ArrayTypeEqualityFunctor> PtrConst;
      typedef Simone::Ptr<ArrayTypeEqualityFunctor> Ptr;

      static Ptr ArrayTypeEqualityFunctorNew(ArrayType::Ptr _type) {
        return new ArrayTypeEqualityFunctor(_type);
      }

      void operator()(Type *_o);
      void operator()(ArrayType *_o);

    private:
      ArrayTypeEqualityFunctor(ArrayType::Ptr _array_type);
  };

  class ArrayTypeSubsumeFunctor : public Type::TypeSubsumeFunctor {
    public:
      typedef Simone::Ptr<const ArrayTypeSubsumeFunctor> PtrConst;
      typedef Simone::Ptr<ArrayTypeSubsumeFunctor> Ptr;

      static Ptr ArrayTypeSubsumeFunctorNew(ArrayType::Ptr _this_type) {
        return new ArrayTypeSubsumeFunctor(_this_type);
      }

      void operator()(Type *_o);
      void operator()(ArrayType *_o);

    private:
      ArrayTypeSubsumeFunctor(ArrayType::Ptr _this_type);
  };

  /* data members */
  Type::Ptr elem_type_;

private:
  bool isArrayType() const { return true; }
};

/* forward declarations */
inline ostream& operator<<(ostream& out, const ArrayType& t) {
  return out << "aeouaoeu" <<endl;
}

#endif
