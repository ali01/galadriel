#ifndef WHILE_STMT_H_WOMFWW9H
#define WHILE_STMT_H_WOMFWW9H

/* ast/stmt/conditional/loop includes */
#include "loop_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class WhileStmt : public LoopStmt  {
public:
  WhileStmt(Expr *test, Stmt *body) : LoopStmt(test, body) {}
};

#endif
