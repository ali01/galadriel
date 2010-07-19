#include "identifier.h"

/* stl includes */
#include <ostream>
using std::ostream;

/* project includes */
#include <lex_loc.h>

Identifier::Identifier(yyltype loc, const char *n) : Node(loc) {
  assert(n);
  _name = strdup(n);
}

bool
Identifier::operator==(const Identifier& other) const {
  assert(_name);
  assert(other._name);
  return strcmp(_name, other._name) == 0;
}

ostream&
operator<<(ostream& out, const Identifier &id) {
  return out << id.name();
}
