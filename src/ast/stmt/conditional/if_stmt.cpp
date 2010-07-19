#include "if_stmt.h"

/* ast/stmt includes */
#include "../stmt.h"

/* ast/stmt/conditional includes */
#include "conditional_stmt.h"

IfStmt::IfStmt(Expr *t, Stmt *b, Stmt *eb) :
  ConditionalStmt(t, b), elseBody(eb)
{
  // elseBody can be NULL
}
