#include "operator.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

Operator::Operator(yyltype loc, op_type _op) : Node(loc), op_type_(_op) {}
