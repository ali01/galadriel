#include "for_stmt.h"

/* simone includes */
#include <simone/utility.h>

/* ast/stmt/expr includes */
#include "../../expr/expr.h"

ForStmt::ForStmt(Simone::Ptr<Expr> init, Simone::Ptr<Expr> test,
                 Simone::Ptr<Expr> step, Stmt::Ptr body) :
  LoopStmt(test, body), init(init), step(step)
{
  assert(init != NULL && test != NULL && step != NULL && body != NULL);
}
