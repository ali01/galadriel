#include "decl.h"

/* simone includes */
#include <simone/utility.h>

/* ast includes */
#include "../identifier.h"

Decl::Decl(Identifier::Ptr n) : Node(*n->lexLoc()), id_(n) {
  assert(n != NULL);
}

Simone::Ptr<Identifier>
Decl::identifier() const {
  return id_;
}

ostream& operator<<(ostream& out, const Decl& d) {
  return out << *d.identifier();
}