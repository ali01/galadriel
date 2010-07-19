#ifndef IDENTIFIER_H_15V2NB3Y
#define IDENTIFIER_H_15V2NB3Y

/* project includes */
#include <lex_loc.h>

/* ast includes */
#include "node.h"

class Identifier : public Node {
public:
  Identifier(yyltype loc, const char *name);

  char *name() const { return _name; }
  bool operator==(const Identifier&) const;

protected:
  char *_name;

private:
  // const string children_str(int _indent_level) const; // TODO: implement

  /* friends */
  friend ostream& operator<<(ostream& out, const Identifier &id);
};

#endif
