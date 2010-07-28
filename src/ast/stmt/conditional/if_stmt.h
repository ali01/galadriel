#ifndef IF_STMT_H_6FD924BD
#define IF_STMT_H_6FD924BD

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/conditional includes */
#include "conditional_stmt.h"

/* forward declarations */
class Expr;
class Stmt;

class IfStmt : public ConditionalStmt {
public:
  typedef Simone::Ptr<const IfStmt> PtrConst;
  typedef Simone::Ptr<IfStmt> Ptr;

  static Ptr IfStmtNew(Simone::Ptr<Expr> test,
                       Simone::Ptr<Stmt> then_body,
                       Simone::Ptr<Stmt> else_body) {
    return new IfStmt(test, then_body, else_body);
  }

  IfStmt(Simone::Ptr<Expr> test,
         Simone::Ptr<Stmt> then_body,
         Simone::Ptr<Stmt> else_body);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

private:
  /* data members */
  Stmt::Ptr else_body_;
};

#endif
