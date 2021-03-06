#ifndef INSTRUCTIONS_H_T6CHSAC4
#define INSTRUCTIONS_H_T6CHSAC4

/* top level */
#include "instruction/load_int_const.h"
#include "instruction/load_str_const.h"
#include "instruction/load_label.h"
#include "instruction/assign.h"
#include "instruction/load.h"
#include "instruction/store.h"
#include "instruction/binary_op.h"
#include "instruction/label.h"
#include "instruction/goto.h"
#include "instruction/ifz.h"
#include "instruction/begin_func.h"
#include "instruction/end_func.h"
#include "instruction/return.h"
#include "instruction/push_param.h"
#include "instruction/pop_params.h"
#include "instruction/v_table.h"

/* fn_call */
#include "instruction/fn_call/l_call.h"
#include "instruction/fn_call/a_call.h"

#endif
