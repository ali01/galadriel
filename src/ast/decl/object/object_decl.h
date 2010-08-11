#ifndef OBJECT_DECL_H_ACU7OGTO
#define OBJECT_DECL_H_ACU7OGTO

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/decl includes */
#include "../decl.h"

/* ast/type includes */
#include "../../type/named_type.h"

/* forward declarations */
class Identifier;

class ObjectDecl : public Decl {
public:
  typedef Simone::Ptr<const ObjectDecl> PtrConst;
  typedef Simone::Ptr<ObjectDecl> Ptr;

  typedef Deque<Decl::Ptr>::const_iterator const_member_iter;
  typedef Deque<Decl::Ptr>::iterator member_iter;

  /* iterator support */
  const_member_iter membersBegin() const { return members_->begin(); }
  member_iter membersBegin() { return members_->begin(); }

  const_member_iter membersEnd() const { return members_->end(); }
  member_iter membersEnd() { return members_->end(); }

  /* member functions */
  void memberInsert(Decl::Ptr _member) { members_->pushBack(_member); }

  NamedType::PtrConst type() const;

  bool indexed() const { return scope_indexed_; }
  void indexedIs(bool _s) { scope_indexed_ = _s; }

  /* override virtual in Node */
  void scopeIs(Simone::Ptr<Scope> _s);

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  ObjectDecl(Simone::Ptr<Identifier> _name, Deque<Decl::Ptr>::Ptr _members);

  /* data members */
  Deque<Decl::Ptr>::Ptr members_;
  NamedType::Ptr this_type_;
  bool scope_indexed_;

private:

  /* disallowed operations */
  ObjectDecl(const ObjectDecl&);
  void operator=(const ObjectDecl&);
};


#endif
