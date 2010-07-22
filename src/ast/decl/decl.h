/* File: decl.h
 * ----------------
 * In our parse tree, Decl nodes are used to represent and
 * manage declarations. There are 4 subclasses of the base class,
 * specialized for declarations of variables, functions, classes,
 * and interfaces.
 *
 * TODO: update comment
 */

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

protected:
  Decl(Simone::Ptr<Identifier> name);

  /* data members */
  Simone::Ptr<Identifier> id_;
  
  /* friends */
  friend ostream& operator<<(ostream& out, const Decl& d) {
    return out << d.id_;
  }
};

#endif
