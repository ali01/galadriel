#ifndef STMT_H_Y19TUBCR
#define STMT_H_Y19TUBCR

/* project includes */
#include "lex_loc.h"

/* ast includes */
#include "../node.h"

class Stmt : public Node {
public:
  Stmt() : Node() {}
  Stmt(yyltype loc) : Node(loc) {}
};


#endif
