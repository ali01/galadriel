#ifndef CLASS_DECL_H_WSH964UZ
#define CLASS_DECL_H_WSH964UZ

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
#include <simone/set.h>
using Simone::Deque;
using Simone::Set;

/* ast includes */
#include "../identifier.h"

/* ast/type includes */
#include "../type/named_type.h"

/* ast/decl includes */
#include "decl.h"

/* forward declarations */
class Identifier;
class Scope;

class ClassDecl : public Decl {
public:
  typedef Simone::Ptr<const ClassDecl> PtrConst;
  typedef Simone::Ptr<ClassDecl> Ptr;

  typedef Deque<Decl::Ptr>::const_iterator const_member_iter;
  typedef Deque<Decl::Ptr>::iterator member_iter;

  typedef Deque<NamedType::Ptr>::const_iterator const_intf_iter;
  typedef Deque<NamedType::Ptr>::iterator intf_iter;

  typedef Set<NamedType::PtrConst,NamedType::less>::const_iterator 
          const_subsumer_iter;
  typedef Set<NamedType::PtrConst,NamedType::less>::iterator
          subsumer_iter;

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


  const_subsumer_iter subsumersBegin() const { return subsumers_.begin(); }
  subsumer_iter subsumersBegin() { return subsumers_.begin(); }

  const_subsumer_iter subsumersEnd() const { return subsumers_.end(); }
  subsumer_iter subsumersEnd() { return subsumers_.end(); }


  /* member functions */

  bool subsumersContain(NamedType::PtrConst _type) const;
  void subsumersInsert(NamedType::PtrConst _type);
  void subsumersInsert(const_subsumer_iter first, const_subsumer_iter last);

  /* attribute member functions */

  NamedType::PtrConst baseClass() const { return base_class_; }
  NamedType::Ptr baseClass() { return base_class_; }

  NamedType::PtrConst type() const { return this_type_; }

  bool scopeIndexed() const { return scope_indexed_; }
  void scopeIndexedIs(bool _s) { scope_indexed_ = _s; }

  /* override virtual in Node */
  ClassDecl::PtrConst enclosingClass() const { return this; }
  void scopeIs(Simone::Ptr<Scope> _s);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  NamedType::Ptr base_class_;
  Deque<NamedType::Ptr>::Ptr interfaces_;
  Deque<Decl::Ptr>::Ptr members_;

  Set<NamedType::PtrConst,NamedType::less> subsumers_;
  NamedType::Ptr this_type_;
  bool scope_indexed_;

  /* operations disallowed */
  ClassDecl(const ClassDecl&);
  void operator=(const ClassDecl&);
};

#endif
