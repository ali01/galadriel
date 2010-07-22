#ifndef STMT_BLOCK_H_KT25NQCB
#define STMT_BLOCK_H_KT25NQCB

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast/stmt includes */
#include "stmt.h"

/* ast/decl includes */
#include "../decl/var_decl.h"

class StmtBlock : public Stmt {
public:
  typedef Simone::Ptr<const StmtBlock> PtrConst;
  typedef Simone::Ptr<StmtBlock> Ptr;

  static Ptr StmtBlockNew(Deque<VarDecl::Ptr>::Ptr var_decls,
                          Deque<Stmt::Ptr>::Ptr stmts) {
    return new StmtBlock(var_decls, stmts);
  }

  StmtBlock(Deque<VarDecl::Ptr>::Ptr var_decls,
            Deque<Stmt::Ptr>::Ptr stmts);

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Deque<VarDecl::Ptr>::Ptr decls;
  Deque<Stmt::Ptr>::Ptr stmts;
};

#endif
