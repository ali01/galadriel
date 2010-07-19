#ifndef EXPR_H_WKQXNJ3E
#define EXPR_H_WKQXNJ3E

/* project includes */
#include "lex_loc.h"

/* stmt includes */
#include "../stmt.h"

class Expr : public Stmt {
public:
  Expr(yyltype loc) : Stmt(loc) {}
  Expr() : Stmt()               {}
};

#endif
