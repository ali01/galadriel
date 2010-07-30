#ifndef NAMED_TYPE_H_895QHUPL
#define NAMED_TYPE_H_895QHUPL

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/type includes */
#include "../type/type.h"

class Identifier;

class NamedType : public Type  {
public:
  typedef Simone::Ptr<const NamedType> PtrConst;
  typedef Simone::Ptr<NamedType> Ptr;

  static Ptr NamedTypeNew(Simone::Ptr<Identifier> i) {
    return new NamedType(i);
  }

  NamedType(Simone::Ptr<Identifier> i);

  /* attribute member functions */
  Simone::Ptr<Identifier> identifier() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  Simone::Ptr<Identifier> id_;
};

#endif
