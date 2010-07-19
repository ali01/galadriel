#ifndef BREAK_STMT_H_JKSGA9PM
#define BREAK_STMT_H_JKSGA9PM

/* project includes */
#include <lex_loc.h>

/* ast/stmt includes */
#include "stmt.h"

class BreakStmt : public Stmt {
public:
  BreakStmt(yyltype loc) : Stmt(loc) {}
};

#endif
