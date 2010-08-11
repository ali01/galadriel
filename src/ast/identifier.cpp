#include "identifier.h"

/* stl includes */
#include <ostream>
using std::ostream;

/* project includes */
#include <lex_location.h>

Identifier::Identifier(yyltype loc, const string& n) : Node(loc), name_(n) {}

bool
Identifier::operator==(const Identifier& other) const {
  return name_ == other.name_;
}

ostream&
operator<<(ostream& out, const Identifier &id) {
  return out << id.name();
}
