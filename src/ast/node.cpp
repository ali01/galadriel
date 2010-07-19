#include "node.h"

/* stl includes */
#include <string>

/* ast includes */
#include "stmt/stmt.h"

/* ast/decl includes */
#include "decl/decl.h"

Node::Node(yyltype loc) {
  location  = new yyltype(loc);
}

Node::Node() {
  location = NULL;
}
