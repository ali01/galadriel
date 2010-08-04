#include "var_access_expr.h"

/* ast includes */
#include "../../../../identifier.h"

VarAccessExpr::VarAccessExpr(Identifier::Ptr _id) : 
  LValueExpr(*_id->lexLoc()), identifier_(_id)
{
  assert(_id != NULL);
}