#ifndef PROGRAM_H_IUK6KVOX
#define PROGRAM_H_IUK6KVOX

/* simone includes */
#include <simone/deque.h>
using Simone::Deque;

/* ast includes */
#include "node.h"

class Program : public Node {
public:
  Program(Deque<Decl*>::Ptr _decl_list);

private:
  /* data members */
  Deque<Decl*>::Ptr decls;

  /* operations disallowed */
  Program(const Program&);
  void operator=(const Program&);
};

#endif
