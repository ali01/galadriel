#ifndef IF_STMT_H_6FD924BD
#define IF_STMT_H_6FD924BD

/* ast/stmt/conditional includes */
#include "conditional_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class IfStmt : public ConditionalStmt {
public:
  IfStmt(Expr *test, Stmt *thenBody, Stmt *elseBody);

private:
  /* data members */
  Stmt *elseBody;
};

#endif
