#include "program.h"

/* simone includes */
#include <simone/utility.h>
#include <simone/deque.h>
using Simone::Deque;

/* ast/decl includes */
#include "decl/decl.h"

Program::Program(Deque<Decl*>::Ptr d) : Node(), decls(d) {
  assert(d != NULL);
}
