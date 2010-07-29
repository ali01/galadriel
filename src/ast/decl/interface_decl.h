#ifndef INTERFACE_DECL_H_CNDLG689
#define INTERFACE_DECL_H_CNDLG689

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast includes */
#include "decl.h"
#include "fn_decl.h"

/* forward declarations */
class Identifier;
class LocalScope;

class InterfaceDecl : public Decl {
public:
  typedef Simone::Ptr<const InterfaceDecl> PtrConst;
  typedef Simone::Ptr<InterfaceDecl> Ptr;

  typedef Deque<FnDecl::Ptr>::const_iterator const_member_iter;
  typedef Deque<FnDecl::Ptr>::iterator member_iter;
  
  static Ptr InterfaceDeclNew(Simone::Ptr<Identifier> name, 
                              Deque<FnDecl::Ptr>::Ptr members) {
    return new InterfaceDecl(name, members);
  }

  InterfaceDecl(Simone::Ptr<Identifier> name, Deque<FnDecl::Ptr>::Ptr members);


  /* iterator support */

  const_member_iter membersBegin() const { return members_->begin(); }
  member_iter membersBegin() { return members_->begin(); }

  const_member_iter membersEnd() const { return members_->end(); }
  member_iter membersEnd() { return members_->end(); }


  /* attribute member functions */

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  bool localScopeIs(Simone::Ptr<LocalScope> _s) { return false; }

  /* data members */
  Deque<FnDecl::Ptr>::Ptr members_;
  
  /* operations disallowed */
  InterfaceDecl(const InterfaceDecl&);
  void operator=(const InterfaceDecl&);
};

#endif
