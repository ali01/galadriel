#ifndef IDENTIFIER_H_15V2NB3Y
#define IDENTIFIER_H_15V2NB3Y

/* stl includes */
#include <string>

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast includes */
#include "node.h"

class Identifier : public Node {
public:
  typedef Simone::Ptr<const Identifier> PtrConst;
  typedef Simone::Ptr<Identifier> Ptr;

  /* map/set comparison functor */
  struct less {
    bool operator()(PtrConst lhs, PtrConst rhs) const {
      return lhs->name() < rhs->name();
    }
  };

  static Ptr IdentifierNew(yyltype loc, const string& name) {
    return new Identifier(loc, name);
  }

  static Ptr IdentifierNew(const string& name) {
    struct yyltype loc;
    memset(&loc, 0x0, sizeof loc);
    return new Identifier(loc, name);
  }

  const string& name() const { return name_; }
  bool operator==(const Identifier&) const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  Identifier(yyltype loc, const string& name);
  
  /* data members */
  const string name_;

  /* friends */
  friend ostream& operator<<(ostream& out, const Identifier &id);
};

#endif
