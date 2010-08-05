#ifndef PRINT_STMT_H_E4OZLL62
#define PRINT_STMT_H_E4OZLL62

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* local includes */
#include "stmt.h"

/* expr includes */
#include "expr/expr.h"

class PrintStmt : public Stmt {
public:
  typedef Simone::Ptr<const PrintStmt> PtrConst;
  typedef Simone::Ptr<PrintStmt> Ptr;

  typedef Deque<Expr::Ptr>::const_iterator const_arg_iterator;
  typedef Deque<Expr::Ptr>::iterator arg_iterator;

  static Ptr PrintStmtNew(Deque<Expr::Ptr>::Ptr _args) {
    return new PrintStmt(_args);
  }

  PrintStmt(Deque<Expr::Ptr>::Ptr _args);

  /* iterator support */
  const_arg_iterator argsBegin() const { return args_->begin(); }
  arg_iterator argsBegin() { return args_->begin(); }

  const_arg_iterator argsEnd() const { return args_->end(); }
  arg_iterator argsEnd() { return args_->end(); }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Deque<Expr::Ptr>::Ptr args_;
};

#endif
