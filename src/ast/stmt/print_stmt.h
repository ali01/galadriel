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
  PrintStmt(Deque<Expr::Ptr>::Ptr arguments);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Deque<Expr::Ptr>::Ptr args;
};

#endif
