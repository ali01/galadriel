#include "object_decl.h"

/* project includes */
#include <scope/scope.h>

/* ast includes */
#include "../../identifier.h"

/* ast/decl includes */
#include "../../decl/fn_decl.h"

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

In::Label::Ptr
ObjectDecl::label() const {
  Identifier::PtrConst id = this->identifier();
  return In::Label::LabelNew(id->name());
}

Deque<In::Label::Ptr>::Ptr
ObjectDecl::functionLabels() const {
  Deque<In::Label::Ptr>::Ptr labels = Deque<In::Label::Ptr>::DequeNew();
  Scope::PtrConst scope = this->scope();

  FnDecl::Ptr fn_decl;
  In::Label::Ptr label;
  string label_name;
  Scope::const_fn_decl_iter it = scope->fnDeclsBegin();
  for (; it != scope->fnDeclsEnd(); ++it) {
    fn_decl = it->second;
    
    string label_name = "_" + this->identifier()->name() + ".";
    label_name += fn_decl->identifier()->name();
    
    label = In::Label::LabelNew(label_name);
    labels->pushBack(label);
  }

  return labels;
}

void
ObjectDecl::scopeIs(Scope::Ptr _s) {
  Node::scopeIs(_s);
  this_type_->scopeIs(_s);
}
