#ifndef SCOPE_H_35KZFJ3E
#define SCOPE_H_35KZFJ3E

/* simone includes */
#include <simone/ptr_interface.h>
#include <simone/map.h>
using Simone::Map;

/* ast includes */
#include "ast/identifier.h"

/* ast/decl includes */
#include "ast/decl/decl.h"

/* instances obtained via factory constructor in ScopeStack class */
class Scope : public Simone::PtrInterface<Scope> {

  /* decl_map_ comparison functor */
  struct IdentifierCompare {
    bool operator()(Identifier::PtrConst lhs, Identifier::PtrConst rhs) const {
      return lhs->name() < rhs->name();
    }
  };

public:
  typedef Simone::Ptr<const Scope> PtrConst;
  typedef Simone::Ptr<Scope> Ptr;

  typedef   
      Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare>::const_iterator 
      const_decl_iter;

  typedef Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare>::iterator 
          decl_iter;

  Decl::PtrConst decl(Identifier::PtrConst _id) const;
  void declIs(Decl::PtrConst _decl);

  const_decl_iter begin() const { return decl_map_.begin(); }
  decl_iter begin() { return decl_map_.begin(); }

  const_decl_iter end() const { return decl_map_.end(); }
  decl_iter end() { return decl_map_.end(); }

private:
  /* private copy constructor called by factory constructor in ScopeStack */
  Scope(const Scope::Ptr& _scope);

  /* data members */
  Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare> decl_map_;

  /* friends */
  friend class ScopeStack;

  /* operations disallowed */
  Scope(const Scope&);
  void operator=(const Scope&);
};

#endif
