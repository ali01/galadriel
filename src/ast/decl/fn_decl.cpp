#include "fn_decl.h"

/* ast includes */
#include "../identifier.h"

/* ast/decl includes */
#include "decl.h"
#include "var_decl.h"

/* ast/stmt includes */
#include "../stmt/stmt_block.h"

/* ast/type includes */
#include "../type/type.h"


FnDecl::FnDecl(Identifier::Ptr n, Type::Ptr r,
               Deque<VarDecl::Ptr>::Ptr d) : Decl(n) {
  assert(n != NULL && r!= NULL && d != NULL);
  body = NULL;
}

void
FnDecl::SetFunctionBody(StmtBlock::Ptr b) {
  // TODO: implement
  assert(b != NULL);
}
