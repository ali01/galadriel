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

  Simone::Ptr<Expr> test() const { return test_; }
  Simone::Ptr<Stmt> body() const { return body_; }

protected:
  ConditionalStmt(Simone::Ptr<Expr> test_expr, Stmt::Ptr body);

private:
  /* data members */
  Simone::Ptr<Expr> test_;
  Simone::Ptr<Stmt> body_;
};

#endif
