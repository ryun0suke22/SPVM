#ifndef SPVM_OP_CHECKER_H
#define SPVM_OP_CHECKER_H

#include "spvm_base.h"

void SPVM_OP_CHECKER_check(SPVM_COMPILER* compiler);

void SPVM_OP_CHECKER_resolve_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_call_sub(SPVM_COMPILER* compiler, SPVM_OP* op_call_sub, SPVM_OP* op_package_current);
void SPVM_OP_CHECKER_resolve_field_access(SPVM_COMPILER* compiler, SPVM_OP* op_field_access);
void SPVM_OP_CHECKER_resolve_package_var_access(SPVM_COMPILER* compiler, SPVM_OP* op_package_var_access, SPVM_OP* op_package);
void SPVM_OP_CHECKER_resolve_basic_types(SPVM_COMPILER* compiler);
void SPVM_OP_CHECKER_resolve_packages(SPVM_COMPILER* compiler);

SPVM_OP* SPVM_OP_CHECKER_check_assign(SPVM_COMPILER* compiler, SPVM_TYPE* dist_type, SPVM_OP* op_src);
void SPVM_OP_CHECKER_apply_unary_string_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_term);
void SPVM_OP_CHECKER_apply_unary_widening_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_unary);
void SPVM_OP_CHECKER_apply_binary_numeric_convertion(SPVM_COMPILER* compiler, SPVM_OP* op_first, SPVM_OP* op_last);

#endif
