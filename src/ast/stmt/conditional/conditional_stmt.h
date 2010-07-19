#ifndef CONDITIONAL_STMT_H_F5X3X2JQ
#define CONDITIONAL_STMT_H_F5X3X2JQ

/* ast/stmt includes */
#include "../stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class ConditionalStmt : public Stmt {
public:
  ConditionalStmt(Expr *testExpr, Stmt *body);

protected:
  /* data members */
  Expr *test;
  Stmt *body;
};

#endif
