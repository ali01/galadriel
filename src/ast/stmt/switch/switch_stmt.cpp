#include "switch_stmt.h"

/* ast/stmt/expr includes */
#include "../expr/expr.h"

/* ast/stmt/switch includes */
#include "switch_case_stmt.h"

SwitchStmt::SwitchStmt(Simone::Ptr<Expr> _test, 
                       Deque<SwitchCaseStmt::Ptr>::Ptr _cases,
                       SwitchCaseStmt::Ptr _default_case) :
test_(_test), cases_(_cases), default_case_(_default_case)
{
  // test_, cases_, and default_case_ can all be NULL
}
