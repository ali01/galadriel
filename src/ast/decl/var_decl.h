#ifndef VAR_DECL_H_NVQQP574
#define VAR_DECL_H_NVQQP574

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include "../identifier.h"

/* ast/decl includes */
#include "decl.h"

/* ast/type includes */
#include "../type/type.h"

class VarDecl : public Decl {
public:
  typedef Simone::Ptr<const VarDecl> PtrConst;
  typedef Simone::Ptr<VarDecl> Ptr;

  static Ptr VarDeclNew(Identifier::Ptr name, Type::Ptr type) {
    return new VarDecl(name, type);
  }

  VarDecl(Identifier::Ptr name, Type::Ptr type);

  Type::Ptr type() const { return type_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Type::Ptr type_;
};

#endif
