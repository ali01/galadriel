#ifndef CALL_H_D5Q44BY5
#define CALL_H_D5Q44BY5

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* project includes */
#include <lex_loc.h>

/* ast/stmt/expr includes */
#include "expr.h"

/* forward declarations */
class Expr;
class Identifier;

/* Like field access, call is used both for qualified base.field()
 * and unqualified field().    We won't figure out until later
 * whether we need implicit "this." so we use one node type for either
 * and sort it out later. */

class CallExpr : public Expr {
public:
  CallExpr(yyltype loc, Expr *base, Identifier *field, Deque<Expr*>::Ptr args);

protected:
  /* base will be null if no explicit base */
  Expr *base;
  Identifier *field;
  Deque<Expr*>::Ptr actuals;
  /* data type compatible with return type of field */
};

#endif
