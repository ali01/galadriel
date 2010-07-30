#include "scope.h"

/* project includes */
#include "error.h"

Scope::Scope(Scope::PtrConst _parent_scope) : parent_scope_(_parent_scope) {
  node_functor_ = NodeFunctor::NodeFunctorNew(this);
}

void
Scope::declIs(Decl::Ptr _decl) {
  Identifier::PtrConst id = _decl->identifier();
  Decl::PtrConst local_decl = decl(id, false);
  if (local_decl == NULL) {
    decls_[id] = _decl;
    _decl->apply(node_functor_);
  } else {
    Error::DeclConflict(_decl, local_decl);
  }
}

void
Scope::baseScopeIs(Scope::PtrConst _base_scope) {
  { 
    Identifier::PtrConst id;
    FnDecl::PtrConst local_fn_decl;
    VarDecl::PtrConst var_decl, local_var_decl;

    const_var_decl_iter vd_it = _base_scope->var_decls_.begin();
    for (; vd_it != _base_scope->var_decls_.end(); ++vd_it) {
      id = vd_it->first;
      var_decl = vd_it->second;

      local_var_decl = varDecl(id, false);
      local_fn_decl = fnDecl(id, false);

      if (local_var_decl == NULL) {
        varDeclIs(var_decl);
      } else {
        Error::DeclConflict(local_var_decl, var_decl);
      }

      if (local_fn_decl != NULL) {
        Error::DeclConflict(local_fn_decl, var_decl);
      }
    }
  }

  {
    Identifier::PtrConst id;
    FnDecl::PtrConst fn_decl, local_fn_decl;
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

Decl::PtrConst
Scope::decl(Identifier::PtrConst _id, bool recursive) const {
  Decl::PtrConst decl = NULL;

  const_decl_iter it = decls_.element(_id);
  if (it != decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->decl(_id);

  return decl;
}

VarDecl::PtrConst
Scope::varDecl(Identifier::PtrConst _id, bool recursive) const {
  VarDecl::PtrConst decl = NULL;

  const_var_decl_iter it = var_decls_.element(_id);
  if (it != var_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->varDecl(_id);

  return decl;
}

FnDecl::PtrConst
Scope::fnDecl(Identifier::PtrConst _id, bool recursive) const {
  FnDecl::PtrConst decl = NULL;

  const_fn_decl_iter it = fn_decls_.element(_id);
  if (it != fn_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->fnDecl(_id);

  return decl;
}

ClassDecl::PtrConst
Scope::classDecl(Identifier::PtrConst _id, bool recursive) const {
  ClassDecl::PtrConst decl = NULL;

  const_class_decl_iter it = class_decls_.element(_id);
  if (it != class_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->classDecl(_id);

  return decl;
}

InterfaceDecl::PtrConst
Scope::interfaceDecl(Identifier::PtrConst _id, bool recursive) const {
  InterfaceDecl::PtrConst decl = NULL;

  const_intf_decl_iter it = intf_decls_.element(_id);
  if (it != intf_decls_.end())
    decl = it->second;

  if (recursive && decl == NULL && parent_scope_ != NULL)
    decl = parent_scope_->interfaceDecl(_id);

  return decl;
}

void
Scope::varDeclIs(VarDecl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  var_decls_[id] = _decl;
}

void
Scope::fnDeclIs(FnDecl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  fn_decls_[id] = _decl;
}

void
Scope::classDeclIs(ClassDecl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  class_decls_[id] = _decl;
}

void
Scope::interfaceDeclIs(InterfaceDecl::PtrConst _decl) {
  Identifier::PtrConst id = _decl->identifier();
  intf_decls_[id] = _decl;
}
