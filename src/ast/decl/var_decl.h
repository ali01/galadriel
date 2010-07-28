#ifndef VAR_DECL_H_NVQQP574
#define VAR_DECL_H_NVQQP574

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include "../identifier.h"

/* ast/decl includes */
#include "decl.h"

class VarDecl : public Decl {
public:
  typedef Simone::Ptr<const VarDecl> PtrConst;
  typedef Simone::Ptr<VarDecl> Ptr;

  static Ptr VarDeclNew(Identifier::Ptr name, Simone::Ptr<Type> type);

  VarDecl(Identifier::Ptr name, Simone::Ptr<Type> type);

  Simone::Ptr<Type> type() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<Type> type_;
};

#endif
