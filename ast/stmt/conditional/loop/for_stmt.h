#ifndef FOR_STMT_H_F6A8WZSU
#define FOR_STMT_H_F6A8WZSU

/* simone includes */
#include <simone/ptr_interface.h>

/* ast/stmt/conditional/loop includes */
#include "loop_stmt.h"

/* forward declarations */
class Expr;

class ForStmt : public LoopStmt {
public:
  typedef Simone::Ptr<const ForStmt> PtrConst;
  typedef Simone::Ptr<ForStmt> Ptr;

  static Ptr ForStmtNew(Simone::Ptr<Expr> init, Simone::Ptr<Expr> test,
                        Simone::Ptr<Expr> step, Stmt::Ptr body) {
    return new ForStmt(init, test, step, body);
  }

  ForStmt(Simone::Ptr<Expr> init, Simone::Ptr<Expr> test,
          Simone::Ptr<Expr> step, Stmt::Ptr body);

  /* attribute member functions */
  Simone::Ptr<Expr> init();
  Simone::Ptr<const Expr> init() const;

  Simone::Ptr<Expr> step();
  Simone::Ptr<const Expr> step() const;

  /* support for double dispatch */
  void self_apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<Expr> init_, step_;
};

#endif
