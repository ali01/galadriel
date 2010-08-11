#include "assign_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_location.h>

/* ast includes */
#include "../../operator.h"

/* ast/type includes */
#include "../../type/type.h"

/* ast/stmt/expr includes */
#include "expr.h"

/* ast/stmt/expr/single_addr includes */
#include "single_addr/single_addr_expr.h"
#include "single_addr/l_value/l_value_expr.h"

AssignExpr::AssignExpr(Simone::Ptr<LValueExpr> _l_val,
                       Simone::Ptr<Operator> _op,
                       Expr::Ptr _rhs) :
  Expr(Join(_l_val->lexLoc(), _rhs->lexLoc())),
  l_value_(_l_val), op_(_op), right_(_rhs)
{
  assert(l_value_ != NULL && op_ != NULL && right_ != NULL);
}

Type::PtrConst
AssignExpr::type() const {
  return l_value_->type();
}
