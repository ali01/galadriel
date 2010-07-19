#ifndef PRINT_STMT_H_E4OZLL62
#define PRINT_STMT_H_E4OZLL62

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* forward declarations */
class Expr;

/* ast/stmt includes */
#include "stmt.h"

class PrintStmt : public Stmt {
public:
  PrintStmt(Deque<Expr*>::Ptr arguments);

private:
  /* data members */
  Deque<Expr*>::Ptr args;
};

#endif
