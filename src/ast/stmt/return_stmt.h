#ifndef RETURN_STMT_H_UUO5Y2SK
#define RETURN_STMT_H_UUO5Y2SK

/* project includes */
#include <lex_loc.h>

/* ast/stmt includes */
#include "stmt.h"

/* forward declarations */
class Expr;

class ReturnStmt : public Stmt {
public:
  ReturnStmt(yyltype loc, Expr *expr);

private:
  /* data members */
  Expr *expr;
};


#endif
