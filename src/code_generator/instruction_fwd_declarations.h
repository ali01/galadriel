#ifndef INSTRUCTION_FWD_DECLARATIONS_H_UTC7A43Q
#define INSTRUCTION_FWD_DECLARATIONS_H_UTC7A43Q

namespace In {

/* top level */
class Instruction;
class LoadIntConst;
class LoadStrConst;
class LoadLabel;
class Assign;
class Load;
class Store;
class BinaryOp;
class Label;
class Goto;
class IfZ;
class BeginFunc;
class EndFunc;
class Return;
class PushParam;
class PopParams;
class VTable;

/* fn_call */
class FnCall;
class LCall;
class ACall;

} /* end of namespace In */

#endif
