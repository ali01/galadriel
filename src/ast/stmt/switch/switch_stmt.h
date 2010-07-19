#ifndef SWITCH_STMT_H_QAC1GHQM
#define SWITCH_STMT_H_QAC1GHQM

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast/stmt includes */
#include "../stmt.h"

/* forward declarations */
class Expr;
class SwitchCaseStmt;

class SwitchStmt : public Stmt {
public:
  SwitchStmt(Expr *test, Deque<SwitchCaseStmt*>::Ptr _cases,
             SwitchCaseStmt *_default_case);

protected:
  Expr *test_;
  Deque<SwitchCaseStmt*>::Ptr cases_;
  SwitchCaseStmt *default_case_;
};

#endif
