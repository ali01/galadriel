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

  typedef Deque<SwitchCaseStmt::Ptr>::const_iterator const_case_iter;
  typedef Deque<SwitchCaseStmt::Ptr>::iterator case_iter;

  static Ptr SwitchStmtNew(Simone::Ptr<Expr> test, 
                           Deque<SwitchCaseStmt::Ptr>::Ptr _cases,
                           SwitchCaseStmt::Ptr _default_case) {
    return new SwitchStmt(test, _cases, _default_case);
  }

  SwitchStmt(Simone::Ptr<Expr> test, Deque<SwitchCaseStmt::Ptr>::Ptr _cases,
             SwitchCaseStmt::Ptr _default_case);

  const_case_iter casesBegin() const { return cases_->begin(); }
  case_iter casesBegin() { return cases_->begin(); }

  const_case_iter casesEnd() const { return cases_->end(); }
  case_iter casesEnd() { return cases_->end(); }

  SwitchCaseStmt::Ptr defaultCase() const { return default_case_; }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  Simone::Ptr<Expr> test_;
  Deque<SwitchCaseStmt::Ptr>::Ptr cases_;
  SwitchCaseStmt::Ptr default_case_;
};

#endif
