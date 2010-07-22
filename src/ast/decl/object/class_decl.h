#ifndef CLASS_DECL_H_WSH964UZ
#define CLASS_DECL_H_WSH964UZ

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include "../../identifier.h"

/* ast/type includes */
#include "../../type/named_type.h"

/* ast/decl includes */
#include "../decl.h"

/* ast/decl/object includes */
#include "object_decl.h"


/* forward declarations */
class Identifier;

class ClassDecl : public ObjectDecl {
public:
  typedef Simone::Ptr<const ClassDecl> PtrConst;
  typedef Simone::Ptr<ClassDecl> Ptr;
  
  static Ptr ClassDeclNew(Identifier::Ptr name, NamedType::Ptr extends,
                          Deque<NamedType::Ptr>::Ptr implements,
                          Deque<Decl::Ptr>::Ptr members) {
    return new ClassDecl(name, extends, implements, members);
  }
  
  ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
            Deque<NamedType::Ptr>::Ptr implements,
            Deque<Decl::Ptr>::Ptr members);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  NamedType::Ptr extends;
  Deque<NamedType::Ptr>::Ptr implements;
};

#endif
