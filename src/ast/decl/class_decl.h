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

  typedef Deque<NamedType::Ptr>::const_iterator const_intf_iter;
  typedef Deque<NamedType::Ptr>::iterator intf_iter;

  static Ptr ClassDeclNew(Identifier::Ptr name, NamedType::Ptr extends,
                          Deque<NamedType::Ptr>::Ptr implements,
                          Deque<Decl::Ptr>::Ptr members) {
    return new ClassDecl(name, extends, implements, members);
  }

  ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
            Deque<NamedType::Ptr>::Ptr implements,
            Deque<Decl::Ptr>::Ptr members);

  /* iterator support */

  const_member_iter membersBegin() const { return members_->begin(); }
  member_iter membersBegin() { return members_->begin(); }

  const_member_iter membersEnd() const { return members_->end(); }
  member_iter membersEnd() { return members_->end(); }


  const_intf_iter interfacesBegin() const { return interfaces_->begin(); }
  intf_iter interfacesBegin() { return interfaces_->begin(); }

  const_intf_iter interfacesEnd() const { return interfaces_->end(); }
  intf_iter interfacesEnd() { return interfaces_->end(); }


  /* attribute member functions */
  NamedType::Ptr baseClass() const { return base_class_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  NamedType::Ptr base_class_;
  Deque<NamedType::Ptr>::Ptr interfaces_;
  Deque<Decl::Ptr>::Ptr members_;

  /* operations disallowed */
  ClassDecl(const ClassDecl&);
  void operator=(const ClassDecl&);
};

#endif
