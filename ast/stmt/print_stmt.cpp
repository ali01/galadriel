#include "print_stmt.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* stmt/expr includes */
#include "expr/single_addr/single_addr_expr.h"

PrintStmt::PrintStmt(Deque<Expr::Ptr>::Ptr _args) : args_(_args) {
  assert(args_ != NULL);
}
