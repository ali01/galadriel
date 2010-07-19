#ifndef OBJECT_DECL_H_OHLTLJPJ
#define OBJECT_DECL_H_OHLTLJPJ

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast/decl includes */
#include "../decl.h"

/* forward declarations */
class Identifier;

class ObjectDecl : public Decl {
protected:
  ObjectDecl(Identifier *n, Deque<Decl*>::Ptr m);

  /* data members */
  Deque<Decl*>::Ptr members;
private:
  ObjectDecl(const ObjectDecl&);
  void operator=(const ObjectDecl&);
};

#endif
