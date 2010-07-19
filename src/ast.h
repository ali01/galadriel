#ifndef AST_H_49460SW5
#define AST_H_49460SW5

/* ast includes */
#include "ast/identifier.h"
#include "ast/operator.h"
#include "ast/program.h"

/* ast/decl includes */
#include "ast/decl/fn_decl.h"
#include "ast/decl/var_decl.h"
#include "ast/decl/object/class_decl.h"
#include "ast/decl/object/interface_decl.h"

/* ast/stmt includes */
#include "ast/stmt/break_stmt.h"
#include "ast/stmt/print_stmt.h"
#include "ast/stmt/return_stmt.h"
#include "ast/stmt/stmt_block.h"
#include "ast/stmt/conditional/conditional_stmt.h"
#include "ast/stmt/conditional/if_stmt.h"
#include "ast/stmt/conditional/loop/for_stmt.h"
#include "ast/stmt/conditional/loop/while_stmt.h"
#include "ast/stmt/expr/assignment_expr.h"
#include "ast/stmt/expr/call_expr.h"
#include "ast/stmt/expr/empty_expr.h"
#include "ast/stmt/expr/null_expr.h"
#include "ast/stmt/expr/single_addr/bool_const_expr.h"
#include "ast/stmt/expr/single_addr/dbl_const_expr.h"
#include "ast/stmt/expr/single_addr/int_const_expr.h"
#include "ast/stmt/expr/single_addr/new_expr.h"
#include "ast/stmt/expr/single_addr/new_array_expr.h"
#include "ast/stmt/expr/single_addr/read_integer_expr.h"
#include "ast/stmt/expr/single_addr/read_line_expr.h"
#include "ast/stmt/expr/single_addr/str_const_expr.h"
#include "ast/stmt/expr/single_addr/compound/arithmetic_expr.h"
#include "ast/stmt/expr/single_addr/compound/equality_expr.h"
#include "ast/stmt/expr/single_addr/compound/logical_expr.h"
#include "ast/stmt/expr/single_addr/compound/postfix_expr.h"
#include "ast/stmt/expr/single_addr/compound/relational_expr.h"
#include "ast/stmt/expr/single_addr/l_value/array_access_expr.h"
#include "ast/stmt/expr/single_addr/l_value/field_access/field_access_expr.h"
#include "ast/stmt/expr/single_addr/l_value/field_access/this_expr.h"
#include "ast/stmt/switch/switch_stmt.h"
#include "ast/stmt/switch/switch_case_stmt.h"

/* ast/type includes */
#include "ast/type/array_type.h"
#include "ast/type/error_type.h"
#include "ast/type/null_type.h"
#include "ast/type/void_type.h"
#include "ast/type/named/class_type.h"
#include "ast/type/named/interface_type.h"

#endif
