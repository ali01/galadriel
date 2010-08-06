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

  typedef Deque<VarDecl::Ptr>::const_iterator const_decl_iter;
  typedef Deque<VarDecl::Ptr>::iterator decl_iter;

  typedef Deque<Stmt::Ptr>::const_iterator const_stmt_iter;
  typedef Deque<Stmt::Ptr>::iterator stmt_iter;

  static Ptr StmtBlockNew(Deque<VarDecl::Ptr>::Ptr var_decls,
                          Deque<Stmt::Ptr>::Ptr stmts) {
    return new StmtBlock(var_decls, stmts);
  }

  StmtBlock(Deque<VarDecl::Ptr>::Ptr var_decls,
            Deque<Stmt::Ptr>::Ptr stmts);

  /* iterator support */

  const_decl_iter declsBegin() const { return decls_->begin(); }
  decl_iter declsBegin() { return decls_->begin(); }

  const_decl_iter declsEnd() const { return decls_->end(); }
  decl_iter declsEnd() { return decls_->end(); }

  const_stmt_iter stmtsBegin() const { return stmts_->begin(); }
  stmt_iter stmtsBegin() { return stmts_->begin(); }

  const_stmt_iter stmtsEnd() const { return stmts_->end(); }
  stmt_iter stmtsEnd() { return stmts_->end(); }


  /* attribute member functions */

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

private:
  /* data members */
  Deque<VarDecl::Ptr>::Ptr decls_;
  Deque<Stmt::Ptr>::Ptr stmts_;
  
  /* operations disallowed */
  StmtBlock(const StmtBlock&);
  void operator=(const StmtBlock&);
};

#endif
