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

  typedef Deque<Decl::Ptr>::iterator decl_iter;
  typedef Deque<Decl::Ptr>::const_iterator const_decl_iter;

  static Ptr ProgramNew(Deque<Decl::Ptr>::Ptr _decl_list) {
    return new Program(_decl_list);
  }

  /* iterator support */

  decl_iter declsBegin() { return decls_->begin(); }
  const_decl_iter declsBegin() const { return decls_->begin(); }
  
  decl_iter declsEnd() { return decls_->end(); }
  const_decl_iter declsEnd() const { return decls_->end(); }


  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Program(Deque<Decl::Ptr>::Ptr _decl_list);

private:
  /* data members */
  Deque<Decl::Ptr>::Ptr decls_;

  /* operations disallowed */
  Program(const Program&);
  void operator=(const Program&);
};

#endif
