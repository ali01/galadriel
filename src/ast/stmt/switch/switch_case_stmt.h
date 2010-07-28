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

  static Ptr SwitchCaseStmtNew(IntConstExpr::Ptr label,
                               Deque<Stmt::Ptr>::Ptr body,
                               bool _is_default=false) {
    return new SwitchCaseStmt(label, body, _is_default);
  }

  SwitchCaseStmt(IntConstExpr::Ptr label,
                 Deque<Stmt::Ptr>::Ptr body,
                 bool _is_default=false);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

protected:
  IntConstExpr::Ptr case_label_;
  Deque<Stmt::Ptr>::Ptr body_;
  
  // TODO: think about this
  bool is_default_;
};

#endif
