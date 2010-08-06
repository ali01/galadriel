#include "loop_stmt.h"

#include "../../expr/expr.h"

LoopStmt::LoopStmt(Expr::Ptr _test_expr, Stmt::Ptr _body) : 
  ConditionalStmt(_test_expr, _body) {}
