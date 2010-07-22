#include "print_stmt.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* stmt/expr includes */
#include "expr/single_addr/single_addr_expr.h"

PrintStmt::PrintStmt(Deque<Expr::Ptr>::Ptr a) : Stmt(), args(a) {
  assert(a != NULL);
}
