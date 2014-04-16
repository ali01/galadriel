#ifndef BREAK_STMT_H_JKSGA9PM
#define BREAK_STMT_H_JKSGA9PM

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt includes */
#include "stmt.h"

class BreakStmt : public Stmt {
public:
  typedef Simone::Ptr<const BreakStmt> PtrConst;
  typedef Simone::Ptr<BreakStmt> Ptr;

  static Ptr BreakStmtNew(yyltype loc) {
    return new BreakStmt(loc);
  }

  BreakStmt(yyltype loc) : Stmt(loc) {}

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }
};

#endif
