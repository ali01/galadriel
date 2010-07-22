#ifndef EXPR_H_WKQXNJ3E
#define EXPR_H_WKQXNJ3E

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include "lex_loc.h"

/* stmt includes */
#include "../stmt.h"

class Expr : public Stmt {
public:
  typedef Simone::Ptr<const Expr> PtrConst;
  typedef Simone::Ptr<Expr> Ptr;

protected:
  Expr(yyltype loc) : Stmt(loc) {}
  Expr() : Stmt()               {}
};

#endif
