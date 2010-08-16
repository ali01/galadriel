#include "object_decl.h"

/* project includes */
#include <scope/scope.h>

/* ast includes */
#include "../../identifier.h"

/* ast/type includes */
#include "../../type/named_type.h"

ObjectDecl::ObjectDecl(Identifier::Ptr _name, Deque<Decl::Ptr>::Ptr _members) :
  Decl(_name),
  members_(_members),
  this_type_(NamedType::NamedTypeNew(_name)),
  scope_indexed_(false)
{
  assert(members_);
  this_type_->parentIs(this);
  this_type_->scopeIs(this->scope());
}

NamedType::PtrConst
ObjectDecl::type() const {
  return this_type_;
}

void
ObjectDecl::scopeIs(Scope::Ptr _s) {
  Node::scopeIs(_s);
  this_type_->scopeIs(_s);
}
