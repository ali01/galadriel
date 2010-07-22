#ifndef PROGRAM_H_IUK6KVOX
#define PROGRAM_H_IUK6KVOX

/* simone includes */
#include <simone/deque.h>
#include <simone/ptr_interface.h>
using Simone::Deque;

/* ast includes */
#include "node.h"

/* ast/decl includes */
#include "decl/decl.h"

class Program : public Node {
public:
  typedef Simone::Ptr<const Program> PtrConst;
  typedef Simone::Ptr<Program> Ptr;

  static Ptr ProgramNew(Deque<Decl::Ptr>::Ptr _decl_list) {
    return new Program(_decl_list);
  }

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Program(Deque<Decl::Ptr>::Ptr _decl_list);

private:
  /* data members */
  Deque<Decl::Ptr>::Ptr decls;

  /* operations disallowed */
  Program(const Program&);
  void operator=(const Program&);
};

#endif
