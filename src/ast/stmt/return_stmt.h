#ifndef RETURN_STMT_H_UUO5Y2SK
#define RETURN_STMT_H_UUO5Y2SK

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_loc.h>

/* ast/stmt includes */
#include "stmt.h"

/* forward declarations */
class Expr;

class ReturnStmt : public Stmt {
public:
  typedef Simone::Ptr<const ReturnStmt> PtrConst;
  typedef Simone::Ptr<ReturnStmt> Ptr;

  static Ptr ReturnStmtNew(yyltype loc, Simone::Ptr<Expr> expr) {
    return new ReturnStmt(loc, expr);
  }

  ReturnStmt(yyltype loc, Simone::Ptr<Expr> expr);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) const { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<Expr> expr;
};

#endif
