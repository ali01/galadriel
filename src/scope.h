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

  /* map comparison functor */
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

  static Ptr ScopeNew() {
    return new Scope();
  }

  Decl::PtrConst decl(Identifier::PtrConst _id) const;
  void declIs(Decl::PtrConst _decl);

  const_decl_iter declsBegin() const { return scope_.begin(); }
  decl_iter declsBegin() { return scope_.begin(); }

  const_decl_iter declsEnd() const { return scope_.end(); }
  decl_iter declsEnd() { return scope_.end(); }

protected:
  Scope() {}
  ~Scope() {}

  /* data members */
  Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare> scope_;
  Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare> local_scope_;
  

private:
  /* private copy constructor called by factory constructor in ScopeStack */
  Scope(const Scope::Ptr& _scope);

  /* operations disallowed */
  Scope(const Scope&);
  void operator=(const Scope&);

  /* friends */
  friend class ScopeStack;
};

#endif
