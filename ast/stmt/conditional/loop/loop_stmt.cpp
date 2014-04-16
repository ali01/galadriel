#include "loop_stmt.h"

#include "../../expr/expr.h"

LoopStmt::LoopStmt(Expr::Ptr _test_expr, Stmt::Ptr _body) : 
  ConditionalStmt(_test_expr, _body) {}

In::Label::Ptr
LoopStmt::endLabel() const {
  return end_label_;
}

void
LoopStmt::endLabelIs(In::Label::Ptr _label) {
  end_label_ = _label;
}
