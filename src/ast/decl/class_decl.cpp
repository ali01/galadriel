#include "class_decl.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <scope.h>

/* ast/type includes */
#include "../type/named_type.h"

ClassDecl::ClassDecl(Identifier::Ptr name, NamedType::Ptr extends,
                     Deque<NamedType::Ptr>::Ptr implements,
                     Deque<Decl::Ptr>::Ptr members) :
  Decl(name),
  base_class_(extends),
  interfaces_(implements),
  members_(members),
  this_type_(NamedType::NamedTypeNew(name))
{
  /* extends can be NULL, impl & mem may be empty lists but cannot be NULL */
  assert(interfaces_ != NULL);
  this_type_->parentIs(this);
  this_type_->scopeIs(this->scope());
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


void
ClassDecl::scopeIs(Scope::Ptr _s) {
  Node::scopeIs(_s);
  this_type_->scopeIs(_s);
}
