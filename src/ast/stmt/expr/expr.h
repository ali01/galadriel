#ifndef EXPR_H_WKQXNJ3E
#define EXPR_H_WKQXNJ3E

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include "lex_location.h"

/* stmt includes */
#include "../stmt.h"

/* forward declarations */
class Location;
class Type;

class Expr : public Stmt {
public:
  typedef Simone::Ptr<const Expr> PtrConst;
  typedef Simone::Ptr<Expr> Ptr;

  virtual Simone::Ptr<const Type> type() const = 0;

  // TODO: think about making const
  virtual Simone::Ptr<Location> location() = 0;
  

protected:
  Expr(yyltype loc) : Stmt(loc) {}
  Expr() : Stmt() {}
};

#endif
