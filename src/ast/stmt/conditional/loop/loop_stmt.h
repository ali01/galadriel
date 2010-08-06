#ifndef LOOP_STMT_H_D19Z9G77
#define LOOP_STMT_H_D19Z9G77

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/conditional includes */
#include "../conditional_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class LoopStmt : public ConditionalStmt {
public:
  typedef Simone::Ptr<const LoopStmt> PtrConst;
  typedef Simone::Ptr<LoopStmt> Ptr;

  LoopStmt::PtrConst enclosingLoop() const { return this; }

protected:
  LoopStmt(Simone::Ptr<Expr> _test_expr, Stmt::Ptr _body);
};

#endif
