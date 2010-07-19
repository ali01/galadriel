#include "operator.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

Operator::Operator(yyltype loc, const char *tok) : Node(loc) {
  assert(tok);
  strncpy(_tokenString, tok, sizeof(_tokenString));
}
