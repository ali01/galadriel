#include "new_expr.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast/decl includes */
#include "../../../decl/class_decl.h"

/* ast/type/named includes */
#include "../../../type/named_type.h"

/* ast/stmt/expr/single_addr includes */
#include "single_addr_expr.h"


NewExpr::NewExpr(yyltype loc, NamedType::Ptr class_type) :
  SingleAddrExpr(loc), type_(class_type)
{
  assert(type_);
}
