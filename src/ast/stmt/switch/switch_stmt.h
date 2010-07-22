#ifndef SWITCH_STMT_H_QAC1GHQM
#define SWITCH_STMT_H_QAC1GHQM

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast/stmt includes */
#include "../stmt.h"

/* local includes */
#include "switch_case_stmt.h"

/* forward declarations */
class Expr;

class SwitchStmt : public Stmt {
public:
  typedef Simone::Ptr<const SwitchStmt> PtrConst;
  typedef Simone::Ptr<SwitchStmt> Ptr;

  static Ptr SwitchStmtNew(Simone::Ptr<Expr> test, 
                           Deque<SwitchCaseStmt::Ptr>::Ptr _cases,
                           SwitchCaseStmt::Ptr _default_case) {
    return new SwitchStmt(test, _cases, _default_case);
  }

  SwitchStmt(Simone::Ptr<Expr> test, Deque<SwitchCaseStmt::Ptr>::Ptr _cases,
             SwitchCaseStmt::Ptr _default_case);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Simone::Ptr<Expr> test_;
  Deque<SwitchCaseStmt::Ptr>::Ptr cases_;
  SwitchCaseStmt::Ptr default_case_;
};

#endif
