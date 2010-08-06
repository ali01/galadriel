#ifndef DECL_H_VE0HILRI
#define DECL_H_VE0HILRI

/* stl includes */
#include <ostream>
using std::ostream;

/* simone includes */
#include <simone/ptr_interface.h>

/* ast includes */
#include "../node.h"

/* forward declarations */
class Identifier;

class Decl : public Node {
public:
  typedef Simone::Ptr<const Decl> PtrConst;
  typedef Simone::Ptr<Decl> Ptr;

  Simone::Ptr<Identifier> identifier() const;

  /* support for double dispatch */
  void apply(Functor::Ptr _functor) { (*_functor)(this); }

protected:
  Decl(Simone::Ptr<Identifier> name);

private:
  /* data members */
  Simone::Ptr<Identifier> id_;
};

/* forward declarations */
ostream& operator<<(ostream& out, const Decl& d);

#endif
