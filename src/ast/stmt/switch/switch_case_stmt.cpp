#include "switch_case_stmt.h"

/* ast/stmt/expr/single_addr includes */
#include "../expr/single_addr/int_const_expr.h"


SwitchCaseStmt::SwitchCaseStmt(Simone::Ptr<IntConstExpr> _label,
                               Deque<Stmt::Ptr>::Ptr _body,
                               bool _is_default) :
  case_label_(_label), body_(_body), is_default_(_is_default)
{
  /* case_label_ and body_ can both be NULL */
  if (body_ == NULL)
    body_ = Deque<Stmt::Ptr>::DequeNew();
}
