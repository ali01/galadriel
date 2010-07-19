main.o: main.cpp utility.h errors.h lex_loc.h parser/parser.h \
  parser/scanner.h ast.h ast/identifier.h lex_loc.h ast/node.h \
  simone/ptr_interface.h simone/exception.h simone/ptr.h simone/utility.h \
  ast/ast_fwd_declarations.h ast/operator.h ast/program.h simone/deque.h \
  simone/ptr_interface.h simone/utility.h ast/decl/fn_decl.h \
  ast/decl/decl.h ast/decl/../node.h ast/decl/var_decl.h \
  ast/decl/object/class_decl.h ast/decl/object/../../identifier.h \
  ast/decl/object/../decl.h ast/decl/object/object_decl.h \
  ast/decl/object/interface_decl.h ast/stmt/break_stmt.h ast/stmt/stmt.h \
  ast/stmt/../node.h ast/stmt/print_stmt.h ast/stmt/return_stmt.h \
  ast/stmt/stmt_block.h ast/stmt/conditional/conditional_stmt.h \
  ast/stmt/conditional/../stmt.h ast/stmt/conditional/if_stmt.h \
  ast/stmt/conditional/conditional_stmt.h \
  ast/stmt/conditional/loop/for_stmt.h \
  ast/stmt/conditional/loop/loop_stmt.h \
  ast/stmt/conditional/loop/../conditional_stmt.h \
  ast/stmt/conditional/loop/while_stmt.h ast/stmt/expr/assignment_expr.h \
  ast/stmt/expr/expr.h ast/stmt/expr/../stmt.h ast/stmt/expr/call_expr.h \
  ast/stmt/expr/empty_expr.h ast/stmt/expr/null_expr.h \
  ast/stmt/expr/single_addr/bool_const_expr.h \
  ast/stmt/expr/single_addr/single_addr_expr.h \
  ast/stmt/expr/single_addr/../expr.h \
  ast/stmt/expr/single_addr/dbl_const_expr.h \
  ast/stmt/expr/single_addr/int_const_expr.h \
  ast/stmt/expr/single_addr/new_expr.h \
  ast/stmt/expr/single_addr/new_array_expr.h \
  ast/stmt/expr/single_addr/read_integer_expr.h \
  ast/stmt/expr/single_addr/read_line_expr.h \
  ast/stmt/expr/single_addr/str_const_expr.h \
  ast/stmt/expr/single_addr/compound/arithmetic_expr.h \
  ast/stmt/expr/single_addr/compound/compound_expr.h \
  ast/stmt/expr/single_addr/compound/../single_addr_expr.h \
  ast/stmt/expr/single_addr/compound/equality_expr.h \
  ast/stmt/expr/single_addr/compound/logical_expr.h \
  ast/stmt/expr/single_addr/compound/postfix_expr.h \
  ast/stmt/expr/single_addr/compound/../l_value/l_value_expr.h \
  ast/stmt/expr/single_addr/compound/../l_value/../single_addr_expr.h \
  ast/stmt/expr/single_addr/compound/relational_expr.h \
  ast/stmt/expr/single_addr/l_value/array_access_expr.h \
  ast/stmt/expr/single_addr/l_value/l_value_expr.h \
  ast/stmt/expr/single_addr/l_value/field_access/field_access_expr.h \
  ast/stmt/expr/single_addr/l_value/field_access/../../../../../identifier.h \
  ast/stmt/expr/single_addr/l_value/field_access/../l_value_expr.h \
  ast/stmt/expr/single_addr/l_value/field_access/this_expr.h \
  ast/stmt/expr/single_addr/l_value/field_access/field_access_expr.h \
  ast/stmt/switch/switch_stmt.h ast/stmt/switch/../stmt.h \
  ast/stmt/switch/switch_case_stmt.h ast/type/array_type.h \
  ast/type/type.h ast/type/../node.h ast/type/error_type.h \
  ast/type/null_type.h ast/type/void_type.h ast/type/named/class_type.h \
  ast/type/named/named_type.h ast/type/named/../type.h \
  ast/type/named/interface_type.h parser/y.tab.h

utility.h:

errors.h:

lex_loc.h:

parser/parser.h:

parser/scanner.h:

ast.h:

ast/identifier.h:

lex_loc.h:

ast/node.h:

simone/ptr_interface.h:

simone/exception.h:

simone/ptr.h:

simone/utility.h:

ast/ast_fwd_declarations.h:

ast/operator.h:

ast/program.h:

simone/deque.h:

simone/ptr_interface.h:

simone/utility.h:

ast/decl/fn_decl.h:

ast/decl/decl.h:

ast/decl/../node.h:

ast/decl/var_decl.h:

ast/decl/object/class_decl.h:

ast/decl/object/../../identifier.h:

ast/decl/object/../decl.h:

ast/decl/object/object_decl.h:

ast/decl/object/interface_decl.h:

ast/stmt/break_stmt.h:

ast/stmt/stmt.h:

ast/stmt/../node.h:

ast/stmt/print_stmt.h:

ast/stmt/return_stmt.h:

ast/stmt/stmt_block.h:

ast/stmt/conditional/conditional_stmt.h:

ast/stmt/conditional/../stmt.h:

ast/stmt/conditional/if_stmt.h:

ast/stmt/conditional/conditional_stmt.h:

ast/stmt/conditional/loop/for_stmt.h:

ast/stmt/conditional/loop/loop_stmt.h:

ast/stmt/conditional/loop/../conditional_stmt.h:

ast/stmt/conditional/loop/while_stmt.h:

ast/stmt/expr/assignment_expr.h:

ast/stmt/expr/expr.h:

ast/stmt/expr/../stmt.h:

ast/stmt/expr/call_expr.h:

ast/stmt/expr/empty_expr.h:

ast/stmt/expr/null_expr.h:

ast/stmt/expr/single_addr/bool_const_expr.h:

ast/stmt/expr/single_addr/single_addr_expr.h:

ast/stmt/expr/single_addr/../expr.h:

ast/stmt/expr/single_addr/dbl_const_expr.h:

ast/stmt/expr/single_addr/int_const_expr.h:

ast/stmt/expr/single_addr/new_expr.h:

ast/stmt/expr/single_addr/new_array_expr.h:

ast/stmt/expr/single_addr/read_integer_expr.h:

ast/stmt/expr/single_addr/read_line_expr.h:

ast/stmt/expr/single_addr/str_const_expr.h:

ast/stmt/expr/single_addr/compound/arithmetic_expr.h:

ast/stmt/expr/single_addr/compound/compound_expr.h:

ast/stmt/expr/single_addr/compound/../single_addr_expr.h:

ast/stmt/expr/single_addr/compound/equality_expr.h:

ast/stmt/expr/single_addr/compound/logical_expr.h:

ast/stmt/expr/single_addr/compound/postfix_expr.h:

ast/stmt/expr/single_addr/compound/../l_value/l_value_expr.h:

ast/stmt/expr/single_addr/compound/../l_value/../single_addr_expr.h:

ast/stmt/expr/single_addr/compound/relational_expr.h:

ast/stmt/expr/single_addr/l_value/array_access_expr.h:

ast/stmt/expr/single_addr/l_value/l_value_expr.h:

ast/stmt/expr/single_addr/l_value/field_access/field_access_expr.h:

ast/stmt/expr/single_addr/l_value/field_access/../../../../../identifier.h:

ast/stmt/expr/single_addr/l_value/field_access/../l_value_expr.h:

ast/stmt/expr/single_addr/l_value/field_access/this_expr.h:

ast/stmt/expr/single_addr/l_value/field_access/field_access_expr.h:

ast/stmt/switch/switch_stmt.h:

ast/stmt/switch/../stmt.h:

ast/stmt/switch/switch_case_stmt.h:

ast/type/array_type.h:

ast/type/type.h:

ast/type/../node.h:

ast/type/error_type.h:

ast/type/null_type.h:

ast/type/void_type.h:

ast/type/named/class_type.h:

ast/type/named/named_type.h:

ast/type/named/../type.h:

ast/type/named/interface_type.h:

parser/y.tab.h:
