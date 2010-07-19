#include "stmt_block.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast includes */
#include "../node.h"

/* ast/decl includes */
#include "../decl/decl.h"
#include "../decl/var_decl.h"

/* ast/stmt includes */
#include "stmt.h"

StmtBlock::StmtBlock(Deque<VarDecl*>::Ptr d, Deque<Stmt*>::Ptr s) :
  Stmt(), decls(d), stmts(s)
{
  assert(d != NULL && s != NULL);
}
