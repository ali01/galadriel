#ifndef LOOP_STMT_H_D19Z9G77
#define LOOP_STMT_H_D19Z9G77

/* ast/stmt/conditional includes */
#include "../conditional_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class LoopStmt : public ConditionalStmt {
public:
  LoopStmt(Expr *testExpr, Stmt *body) : ConditionalStmt(testExpr, body) {}
};

#endif
