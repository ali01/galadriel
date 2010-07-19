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

/* ast includes */
#include "../node.h"

/* forward declarations */
class Identifier;

class Decl : public Node {
public:
  Decl(Identifier *name);

  friend ostream& operator<<(ostream& out, Decl *d) { return out << d->id_; }

protected:
  Identifier *id_;
};

#endif
