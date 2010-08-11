#include "tac_emit_functor.h"

/* stl includes */
#include <iostream>
using std::cout;

#include "instruction_includes.h"
#include "location.h"

void
TACEmitFunctor::operator()(LoadIntConst *nd) {
  cout << *nd->location() << " = " << nd->value();
}
