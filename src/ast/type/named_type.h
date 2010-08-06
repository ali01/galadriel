#ifndef NAMED_TYPE_H_895QHUPL
#define NAMED_TYPE_H_895QHUPL

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include "../identifier.h"

/* ast/type includes */
#include "type.h"


/* forward declarations */
class ClassDecl;

class NamedType : public Type  {
public:
  typedef Simone::Ptr<const NamedType> PtrConst;
  typedef Simone::Ptr<NamedType> Ptr;

  /* comparison functor */
  struct less {
    bool operator()(PtrConst lhs, PtrConst rhs) const {
      Identifier::less id_cmp;
      return id_cmp(lhs->identifier(), rhs->identifier());
    }
  };

  static Ptr NamedTypeNew(Identifier::Ptr i) {
    return new NamedType(i);
  }

  NamedType(Identifier::Ptr i);

  /* attribute member functions */
  Identifier::Ptr identifier();
  Identifier::PtrConst identifier() const;

  Simone::Ptr<ClassDecl> classDecl();
  Simone::Ptr<const ClassDecl> classDecl() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  class NamedTypeEqualityFunctor : public Type::TypeEqualityFunctor {
    public:
      typedef Simone::Ptr<const NamedTypeEqualityFunctor> PtrConst;
      typedef Simone::Ptr<NamedTypeEqualityFunctor> Ptr;

      static Ptr NamedTypeEqualityFunctorNew(NamedType::Ptr _type) {
        return new NamedTypeEqualityFunctor(_type);
      }

      void operator()(Type *_o) { equal_ = false; }
      void operator()(NamedType *_o);
    
    private:
      NamedTypeEqualityFunctor(NamedType::Ptr _type);
  };

  class NamedTypeSubsumeFunctor : public Type::TypeSubsumeFunctor {
    public:
      typedef Simone::Ptr<const NamedTypeSubsumeFunctor> PtrConst;
      typedef Simone::Ptr<NamedTypeSubsumeFunctor> Ptr;

      static Ptr NamedTypeSubsumeFunctorNew(NamedType::Ptr _this_type) {
        return new NamedTypeSubsumeFunctor(_this_type);
      }

      void operator()(Type *_o) { subsumes_other_ = false; }
      void operator()(NamedType *_o);

    private:
      NamedTypeSubsumeFunctor(NamedType::Ptr _this_type);
  };

  /* data members */
  Identifier::Ptr id_;
};

#endif
