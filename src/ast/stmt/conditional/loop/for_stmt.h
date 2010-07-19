#ifndef FOR_STMT_H_F6A8WZSU
#define FOR_STMT_H_F6A8WZSU

/* ast/stmt/conditional/loop includes */
#include "loop_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class ForStmt : public LoopStmt {
public:
  ForStmt(Expr *init, Expr *test, Expr *step, Stmt *body);

private:
  /* data members */
  Expr *init, *step;
};

#endif
