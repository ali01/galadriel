#ifndef ARRAY_TYPE_H_J35FQYOQ
#define ARRAY_TYPE_H_J35FQYOQ

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

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

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  /* data members */
  Type::Ptr elem_type_;
};

#endif
