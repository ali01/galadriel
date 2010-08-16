#ifndef CLASS_DECL_H_WSH964UZ
#define CLASS_DECL_H_WSH964UZ

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
#include <simone/set.h>
using Simone::Deque;
using Simone::Set;

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
class InterfaceDecl;
class Scope;

class ClassDecl : public ObjectDecl {
public:
  typedef Simone::Ptr<const ClassDecl> PtrConst;
  typedef Simone::Ptr<ClassDecl> Ptr;

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

  static Ptr ClassDeclNew(Identifier::Ptr name) {
    Deque<NamedType::Ptr>::Ptr intf = Deque<NamedType::Ptr>::DequeNew();
    Deque<Decl::Ptr>::Ptr members = Deque<Decl::Ptr>::DequeNew();
    return new ClassDecl(name, NULL, intf, members);
  }

  ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
            Deque<NamedType::Ptr>::Ptr implements,
            Deque<Decl::Ptr>::Ptr members);

  /* iterator support */

  const_intf_iter interfacesBegin() const { return interfaces_->begin(); }
  intf_iter interfacesBegin() { return interfaces_->begin(); }

  const_intf_iter interfacesEnd() const { return interfaces_->end(); }
  intf_iter interfacesEnd() { return interfaces_->end(); }


  const_subsumer_iter subsumersBegin() const { return subsumers_.begin(); }
  subsumer_iter subsumersBegin() { return subsumers_.begin(); }

  const_subsumer_iter subsumersEnd() const { return subsumers_.end(); }
  subsumer_iter subsumersEnd() { return subsumers_.end(); }


  /* attribute member functions */

  bool subsumersContain(NamedType::PtrConst _type) const;
  void subsumersInsert(NamedType::PtrConst _type);
  void subsumersInsert(const_subsumer_iter first, const_subsumer_iter last);

  NamedType::PtrConst baseClass() const { return base_class_; }
  NamedType::Ptr baseClass() { return base_class_; }
  ClassDecl::Ptr baseClassDecl();

  bool implementsInterface(Simone::Ptr<const InterfaceDecl> _interface) const;

  bool isLibraryStub() const { return is_library_stub_; }
  void isLibraryStubIs(bool _s) { is_library_stub_ = true; }

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* override virtual in Node */
  ClassDecl::PtrConst nearestClass() const { return this; }

  /* data members */
  NamedType::Ptr base_class_;
  Deque<NamedType::Ptr>::Ptr interfaces_;

  Set<NamedType::PtrConst,NamedType::less> subsumers_;

  bool is_library_stub_;

  /* operations disallowed */
  ClassDecl(const ClassDecl&);
  void operator=(const ClassDecl&);
};

#endif
