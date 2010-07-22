#ifndef IDENTIFIER_H_15V2NB3Y
#define IDENTIFIER_H_15V2NB3Y

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

class Identifier : public Node {
public:
  typedef Simone::Ptr<const Identifier> PtrConst;
  typedef Simone::Ptr<Identifier> Ptr;

  static Ptr IdentifierNew(yyltype loc, const char *name) {
    return new Identifier(loc, name);
  }

  char *name() const { return _name; }
  bool operator==(const Identifier&) const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Identifier(yyltype loc, const char *name);
  
  /* data members */
  char *_name;

  /* friends */
  friend ostream& operator<<(ostream& out, const Identifier &id);
};

#endif
