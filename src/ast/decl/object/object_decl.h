#ifndef OBJECT_DECL_H_OHLTLJPJ
#define OBJECT_DECL_H_OHLTLJPJ

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast/decl includes */
#include "../decl.h"

/* forward declarations */
class Identifier;

class ObjectDecl : public Decl {
public:
  typedef Simone::Ptr<const ObjectDecl> PtrConst;
  typedef Simone::Ptr<ObjectDecl> Ptr;

protected:
  ObjectDecl(Simone::Ptr<Identifier> name, Deque<Decl::Ptr>::Ptr members);

  /* data members */
  Deque<Decl::Ptr>::Ptr members;

private:
  ObjectDecl(const ObjectDecl&);
  void operator=(const ObjectDecl&);
};

#endif
