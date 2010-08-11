#ifndef INTERFACE_DECL_H_CNDLG689
#define INTERFACE_DECL_H_CNDLG689

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast/decl includes */
#include "../decl.h"

/* ast/decl/object includes */
#include "object_decl.h"

/* forward declarations */
class Identifier;

class InterfaceDecl : public ObjectDecl {
public:
  typedef Simone::Ptr<const InterfaceDecl> PtrConst;
  typedef Simone::Ptr<InterfaceDecl> Ptr;

  
  static Ptr InterfaceDeclNew(Simone::Ptr<Identifier> name, 
                              Deque<Decl::Ptr>::Ptr members) {
    return new InterfaceDecl(name, members);
  }

  InterfaceDecl(Simone::Ptr<Identifier> name, Deque<Decl::Ptr>::Ptr members);


  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  
  /* operations disallowed */
  InterfaceDecl(const InterfaceDecl&);
  void operator=(const InterfaceDecl&);
};

#endif
