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

StmtBlock::StmtBlock(Deque<VarDecl::Ptr>::Ptr var_decls,
                     Deque<Stmt::Ptr>::Ptr stmts) :
  Stmt(), decls_(var_decls), stmts_(stmts)
{
  assert(var_decls != NULL && stmts != NULL);
}
