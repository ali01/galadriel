#ifndef RETURN_STMT_H_UUO5Y2SK
#define RETURN_STMT_H_UUO5Y2SK

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include <lex_location.h>

/* ast/stmt includes */
#include "stmt.h"

/* forward declarations */
class Expr;

class ReturnStmt : public Stmt {
public:
  typedef Simone::Ptr<const ReturnStmt> PtrConst;
  typedef Simone::Ptr<ReturnStmt> Ptr;

  static Ptr ReturnStmtNew(yyltype _loc, Simone::Ptr<Expr> _expr) {
    return new ReturnStmt(_loc, _expr);
  }

  ReturnStmt(yyltype _loc, Simone::Ptr<Expr> _expr);

  /* attribute member functions */
  Simone::Ptr<Expr> expr();
  Simone::Ptr<const Expr> expr() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Simone::Ptr<Expr> expr_;
};

#endif
