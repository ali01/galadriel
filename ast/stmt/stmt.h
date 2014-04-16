#ifndef STMT_H_Y19TUBCR
#define STMT_H_Y19TUBCR

/* simone includes */
#include <simone/ptr_interface.h>

/* project includes */
#include "lex_location.h"

/* ast includes */
#include "../node.h"

class Stmt : public Node {
public:
  typedef Simone::Ptr<const Stmt> PtrConst;
  typedef Simone::Ptr<Stmt> Ptr;

protected:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
};

#endif
