#ifndef SWITCH_CASE_STMT_H_F55KX2CK
#define SWITCH_CASE_STMT_H_F55KX2CK

/* project includes */
#include <simone/ptr_interface.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/stmt includes */
#include "../stmt.h"

/* ast/expr includes */
#include "../expr/single_addr/int_const_expr.h"

class SwitchCaseStmt : public Stmt {
public:
  typedef Simone::Ptr<const SwitchCaseStmt> PtrConst;
  typedef Simone::Ptr<SwitchCaseStmt> Ptr;

  typedef Deque<Stmt::Ptr>::const_iterator const_stmt_iter;
  typedef Deque<Stmt::Ptr>::iterator stmt_iter;

  static Ptr SwitchCaseStmtNew(IntConstExpr::Ptr label,
                               Deque<Stmt::Ptr>::Ptr body,
                               bool _is_default=false) {
    return new SwitchCaseStmt(label, body, _is_default);
  }

  SwitchCaseStmt(IntConstExpr::Ptr label,
                 Deque<Stmt::Ptr>::Ptr body,
                 bool _is_default=false);

  const_stmt_iter stmtsBegin() const { return body_->begin(); }
  stmt_iter stmtsBegin() { return body_->begin(); }

  const_stmt_iter stmtsEnd() const { return body_->end(); }
  stmt_iter stmtsEnd() { return body_->end(); }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  IntConstExpr::Ptr case_label_;
  Deque<Stmt::Ptr>::Ptr body_;
  
  // TODO: think about this
  bool is_default_;
};

#endif
