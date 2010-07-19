#ifndef SWITCH_CASE_STMT_H_F55KX2CK
#define SWITCH_CASE_STMT_H_F55KX2CK

/* project includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast/stmt includes */
#include "../stmt.h"

/* forward declarations */
class IntConstExpr;
class Stmt;

class SwitchCaseStmt : public Stmt {
public:
  SwitchCaseStmt(IntConstExpr *label, Deque<Stmt*>::Ptr body,
                 bool _is_default=false);

protected:
  IntConstExpr *case_label_;
  Deque<Stmt*>::Ptr body_;
  bool is_default_;
};

#endif
