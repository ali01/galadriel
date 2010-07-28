#ifndef CLASS_DECL_H_WSH964UZ
#define CLASS_DECL_H_WSH964UZ

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast includes */
#include "../identifier.h"

/* ast/type includes */
#include "../type/named_type.h"

/* ast/decl includes */
#include "decl.h"


/* forward declarations */
class Identifier;

class ClassDecl : public Decl {
public:
  typedef Simone::Ptr<const ClassDecl> PtrConst;
  typedef Simone::Ptr<ClassDecl> Ptr;

  typedef Deque<Decl::Ptr>::const_iterator const_member_iter;
  typedef Deque<Decl::Ptr>::iterator member_iter;

  static Ptr ClassDeclNew(Identifier::Ptr name, NamedType::Ptr extends,
                          Deque<NamedType::Ptr>::Ptr implements,
                          Deque<Decl::Ptr>::Ptr members) {
    return new ClassDecl(name, extends, implements, members);
  }
  
  ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
            Deque<NamedType::Ptr>::Ptr implements,
            Deque<Decl::Ptr>::Ptr members);

  const_member_iter membersBegin() const { return members_->begin(); }
  member_iter membersBegin() { return members_->begin(); }

  const_member_iter membersEnd() const { return members_->end(); }
  member_iter membersEnd() { return members_->end(); }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

private:
  /* data members */
  NamedType::Ptr extends;
  Deque<NamedType::Ptr>::Ptr implements;
  Deque<Decl::Ptr>::Ptr members_;
  
  /* operations disallowed */
  ClassDecl(const ClassDecl&);
  void operator=(const ClassDecl&);
};

#endif
