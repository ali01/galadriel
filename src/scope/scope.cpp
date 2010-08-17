#include "scope.h"

/* project includes */
#include <error.h>

Scope::Scope(Scope::Ptr _parent_scope) : parent_scope_(_parent_scope.ptr()) {
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
  if (parent_scope_ != NULL)
    parent_scope_->childInsert(this);
}

void
Scope::declIs(Decl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  Decl::PtrConst local_decl = decl(id, false);
  if (local_decl == NULL) {
    decls_[id] = _decl;
    node_functor_(_decl);
  } else {
    Error::DeclConflict(_decl, local_decl);
  }
}

void
Scope::baseScopeIs(Scope::PtrConst _base_scope) {
  { /* inherit variable declarations */
    Identifier::PtrConst id;
    FnDecl::PtrConst local_fn_decl;
    VarDecl::Ptr var_decl, local_var_decl;

    const_var_decl_iter vd_it = _base_scope->var_decls_.begin();
    for (; vd_it != _base_scope->var_decls_.end(); ++vd_it) {
      id = vd_it->first;
      var_decl = vd_it->second;

      local_var_decl = varDecl(id, false);
      local_fn_decl = fnDecl(id, false);

      if (local_var_decl == NULL) {
        varDeclIs(var_decl);
      } else {
        /* conflict between var_decls */
        Error::DeclConflict(local_var_decl, var_decl);
      }

      if (local_fn_decl != NULL) {
        /* conflict between var_decl and fn_decl */
        Error::DeclConflict(local_fn_decl, var_decl);
      }
    }
  }

  { /* inherit function declarations */
    Identifier::PtrConst id;
    FnDecl::Ptr fn_decl, local_fn_decl;
    VarDecl::PtrConst local_var_decl;
    const_fn_decl_iter fn_it = _base_scope->fn_decls_.begin();
    for (; fn_it != _base_scope->fn_decls_.end(); ++fn_it) {
      id = fn_it->first;
      fn_decl = fn_it->second;

      local_fn_decl = fnDecl(id, false);
      local_var_decl = varDecl(id, false);

      if (local_fn_decl == NULL) {
        if (local_var_decl == NULL) {
          fnDeclIs(fn_decl);
        } else {
          /* conflict between fn_decl and local var_decl */
          Error::DeclConflict(local_var_decl, fn_decl);
        }
      } else {
        if (local_var_decl != NULL) {
          Error::DeclConflict(local_var_decl, fn_decl);
        } else if (*local_fn_decl != *fn_decl) {
          Error::OverrideMismatch(local_fn_decl);
        }
      }
    }
  }
}

Decl::Ptr
Scope::decl(Identifier::PtrConst _id, bool recursive) {
  Decl::Ptr decl = NULL;

  const_decl_iter it = decls_.element(_id);
  if (it != decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->decl(_id);

  return decl;
}

VarDecl::Ptr
Scope::varDecl(Identifier::PtrConst _id, bool recursive) {
  VarDecl::Ptr decl = NULL;

  const_var_decl_iter it = var_decls_.element(_id);
  if (it != var_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->varDecl(_id);

  return decl;
}

FnDecl::Ptr
Scope::fnDecl(Identifier::PtrConst _id, bool recursive) {
  FnDecl::Ptr decl = NULL;

  const_fn_decl_iter it = fn_decls_.element(_id);
  if (it != fn_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->fnDecl(_id);

  return decl;
}

ObjectDecl::Ptr
Scope::objectDecl(Identifier::PtrConst _id, bool recursive) {
  ObjectDecl::Ptr decl = classDecl(_id, recursive);
  if (decl == NULL)
    decl = interfaceDecl(_id, recursive);

  return decl;
}

ClassDecl::Ptr
Scope::classDecl(Identifier::PtrConst _id, bool recursive) {
  ClassDecl::Ptr decl = NULL;

  const_class_decl_iter it = class_decls_.element(_id);
  if (it != class_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->classDecl(_id);

  return decl;
}

InterfaceDecl::Ptr
Scope::interfaceDecl(Identifier::PtrConst _id, bool recursive) {
  InterfaceDecl::Ptr decl = NULL;

  const_intf_decl_iter it = intf_decls_.element(_id);
  if (it != intf_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->interfaceDecl(_id);

  return decl;
}

Decl::PtrConst
Scope::decl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->decl(_id, recursive);
}

VarDecl::PtrConst
Scope::varDecl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->varDecl(_id, recursive);
}

FnDecl::PtrConst
Scope::fnDecl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->fnDecl(_id, recursive);
}

ObjectDecl::PtrConst
Scope::objectDecl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->objectDecl(_id, recursive);
}

ClassDecl::PtrConst
Scope::classDecl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->classDecl(_id, recursive);
}

InterfaceDecl::PtrConst
Scope::interfaceDecl(Identifier::PtrConst _id, bool recursive) const {
  Scope::Ptr me = const_cast<Scope*>(this);
  return me->interfaceDecl(_id, recursive);
}

void
Scope::varDeclIs(VarDecl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  var_decls_[id] = _decl;
}

void
Scope::fnDeclIs(FnDecl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  fn_decls_[id] = _decl;
}

void
Scope::classDeclIs(ClassDecl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  class_decls_[id] = _decl;
}

void
Scope::interfaceDeclIs(InterfaceDecl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  intf_decls_[id] = _decl;
}
