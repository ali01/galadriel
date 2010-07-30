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

  /* private iterator typedefs */
  typedef
    Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare>::const_iterator
    const_decl_iter;

  typedef
    Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare>::iterator
    decl_iter;

public:
  typedef Simone::Ptr<const Scope> PtrConst;
  typedef Simone::Ptr<Scope> Ptr;

  Decl::PtrConst decl(Identifier::PtrConst _id) const;
  void declIs(Decl::PtrConst _decl);

protected:
  ~Scope() {}

  /* data members */
  Map<Identifier::PtrConst,Decl::PtrConst,IdentifierCompare> scope_;
  Scope::PtrConst parent_scope_;

private:
  /* private constructor called by factory constructor in ScopeStack */
  explicit Scope(Scope::PtrConst _parent_scope);

  /* operations disallowed */
  Scope(const Scope&);
  void operator=(const Scope&);

  /* friends */
  friend class ScopeStack;
};

#endif
