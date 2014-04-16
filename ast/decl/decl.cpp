#include "decl.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../identifier.h"

Decl::Decl(Identifier::Ptr n) : Node(*n->lexLoc()), id_(n) {
  assert(n != NULL);
}

Identifier::PtrConst
Decl::identifier() const {
  return id_;
}

Identifier::Ptr
Decl::identifier() {
  return id_;
}

ostream& operator<<(ostream& out, const Decl& d) {
  return out << *d.identifier();
}