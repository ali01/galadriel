#ifndef LOOP_STMT_H_D19Z9G77
#define LOOP_STMT_H_D19Z9G77

/* simone includes */
#include <simone/ptr_interface.h>

#include <code_generator/instruction/label.h>

/* ast/stmt/conditional includes */
#include "../conditional_stmt.h"

/* forward declarations */
class Expr;

class LoopStmt : public ConditionalStmt {
public:
  typedef Simone::Ptr<const LoopStmt> PtrConst;
  typedef Simone::Ptr<LoopStmt> Ptr;

  In::Label::Ptr endLabel() const;
  void endLabelIs(In::Label::Ptr _label);

protected:
  LoopStmt(Simone::Ptr<Expr> _test_expr, Stmt::Ptr _body);

  /* override */
  LoopStmt::PtrConst nearestLoop() const { return this; }

  /* data members */
  In::Label::Ptr end_label_;
};

#endif
