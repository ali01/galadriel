#ifndef CONDITIONAL_STMT_H_F5X3X2JQ
#define CONDITIONAL_STMT_H_F5X3X2JQ

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt includes */
#include "../stmt.h"

/* forward declarations */
class Expr;

class ConditionalStmt : public Stmt {
public:
  typedef Simone::Ptr<const ConditionalStmt> PtrConst;
  typedef Simone::Ptr<ConditionalStmt> Ptr;

protected:
  ConditionalStmt(Simone::Ptr<Expr> test_expr, Stmt::Ptr body);

  /* data members */
  Simone::Ptr<Expr> test;
  Simone::Ptr<Stmt> body;
};

#endif
