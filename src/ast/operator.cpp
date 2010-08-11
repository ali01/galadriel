#include "operator.h"

/* simone includes */
#include <simone/utility.h>

/* project includes */
#include <lex_location.h>

/* ast includes */
#include "node.h"

Operator::Operator(yyltype loc, op_type _op) : Node(loc), op_type_(_op) {}

ostream&
operator<<(ostream& out, const Operator& _op) {
  switch (_op.operatorType()) {
    case Operator::kAdd:            return out << "+";
    case Operator::kSubtract:       return out << "-";
    case Operator::kMultiply:       return out << "*";
    case Operator::kDivide:         return out << "/";
    case Operator::kModulo:         return out << "%";
    case Operator::kEqual:          return out << "==";
    case Operator::kNotEqual:       return out << "!=";
    case Operator::kLess:           return out << "<";
    case Operator::kLessEqual:      return out << "<=";
    case Operator::kGreater:        return out << ">";
    case Operator::kGreaterEqual:   return out << ">=";
    case Operator::kAnd:            return out << "&&";
    case Operator::kOr:             return out << "||";
    case Operator::kNot:            return out << "!";
    case Operator::kAssign:         return out << "=";
    default:
      out << " unknown operator ";
  }

  return out;
}
