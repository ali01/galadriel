#include "class_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <scope/scope.h>

/* ast/decl includes */
#include "interface_decl.h"

/* ast/type includes */
#include "../../type/named_type.h"

ClassDecl::ClassDecl(Identifier::Ptr _name, NamedType::Ptr _extends,
                     Deque<NamedType::Ptr>::Ptr _implements,
                     Deque<Decl::Ptr>::Ptr _members) :
  ObjectDecl(_name, _members),
  base_class_(_extends),
  interfaces_(_implements)
{
  /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
  assert(interfaces_ != NULL);
}

bool
ClassDecl::subsumersContain(NamedType::PtrConst _type) const {
  if (*this_type_ == *_type)
    return true;
  
  const_subsumer_iter it = subsumers_.element(_type);
  return it != subsumers_.end();
}

void
ClassDecl::subsumersInsert(NamedType::PtrConst _type) {
  subsumers_.elementIs(_type);
}

void
ClassDecl::subsumersInsert(const_subsumer_iter first,
                           const_subsumer_iter last) {
  subsumers_.insert(first, last);
}


ClassDecl::Ptr
ClassDecl::baseClassDecl() {
  ClassDecl::Ptr base_decl = NULL;

  NamedType::Ptr base_class_type = baseClass();
  if (base_class_type != NULL) {
    /* obtain base class identifier */
    Identifier::Ptr base_id = base_class_type->identifier();

    /* search for base class decl in scope */
    Scope::Ptr scope = this->scope();
    base_decl = scope->classDecl(base_id);
  }

  return base_decl;
}


bool
ClassDecl::implementsInterface(InterfaceDecl::PtrConst _interface) const {
  bool ret = true;

  Decl::PtrConst intf_member, this_member;
  Scope::PtrConst scope = this->scope();
  InterfaceDecl::const_member_iter it = _interface->membersBegin();
  for (; it != _interface->membersEnd(); ++it) {
    intf_member = *it;
    this_member = scope->fnDecl(intf_member->identifier(), false);
    if (this_member == NULL) {
      ret = false;
      break;
    }
  }

  return ret;
}
