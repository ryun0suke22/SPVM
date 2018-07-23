#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <stddef.h>

#include "spvm_csource_builder.h"
#include "spvm_string_buffer.h"
#include "spvm_sub.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_hash.h"
#include "spvm_type.h"
#include "spvm_object.h"
#include "spvm_runtime.h"
#include "spvm_type.h"
#include "spvm_my.h"
#include "spvm_opcode.h"
#include "spvm_opcode_array.h"
#include "spvm_runtime_api.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"
#include "spvm_opcode_array.h"
#include "spvm_constant.h"
#include "spvm_basic_type.h"
#include "spvm_package_var.h"
#include "spvm_package_var_access.h"
#include "spvm_field_access.h"
#include "spvm_call_sub.h"
#include "spvm_switch_info.h"
#include "spvm_case_info.h"
#include "spvm_var.h"
#include "spvm_call_sub.h"

void SPVM_CSOURCE_BUILDER_add_var(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t index) {
  (void)compiler;
  
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "vars[");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
}

void SPVM_CSOURCE_BUILDER_add_var_offset(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, int32_t index, int32_t offset) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "vars[");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " + ");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , offset);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
}

void SPVM_CSOURCE_BUILDER_add_operand(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)&");
  SPVM_CSOURCE_BUILDER_add_var(compiler, string_buffer, var_index);
}

void SPVM_CSOURCE_BUILDER_add_stack(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)&");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "stack[");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , var_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
}

void SPVM_CSOURCE_BUILDER_add_operand_offset(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t var_index, int32_t offset) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)&");
  SPVM_CSOURCE_BUILDER_add_var_offset(compiler, string_buffer, var_index, offset);
}

void SPVM_CSOURCE_BUILDER_add_bool(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = !!");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_eq(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " == ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_ne(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " != ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_gt(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " > ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_ge(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " >= ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_lt(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " < ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_le(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " <= ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_add(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " + ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_subtract(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " - ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_multiply(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " * ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_divide_integral(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " == 0, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, env->new_string_raw(env, \"0 division\", 0));\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = 1;\n");

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } else {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " / ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_divide_floating_point(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " / ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_remainder_integral(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (__builtin_expect(");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " == 0, 0)) {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* exception = env->new_string_raw(env, \"0 division\", 0);\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, exception);\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  else {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " % /* REMAINDER */ "); // % have undarstandable bug.
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
}

void SPVM_CSOURCE_BUILDER_add_left_shift(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " << (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  if (strcmp(type_name, "SPVM_VALUE_int") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x1f))");
  }
  else if (strcmp(type_name, "SPVM_VALUE_long") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_right_shift_unsigned(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ((");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ")((u");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ")");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " >> (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  if (strcmp(type_name, "int32_t") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x1f))");
  }
  else if (strcmp(type_name, "int64_t") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
}

void SPVM_CSOURCE_BUILDER_add_right_shift(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " >> (");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  if (strcmp(type_name, "SPVM_VALUE_int") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x1f))");
  }
  else if (strcmp(type_name, "SPVM_VALUE_long") == 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , " & 0x3f))");
  }
  else {
    assert(0);
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_bit_and(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " & ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_bit_or(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " | ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_bit_xor(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in1_index, int32_t in2_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in1_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " ^ ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in2_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_negate(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = -");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_plus(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_complement(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ~");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_inc(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t number) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " += ");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , number);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_convert(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* out_type_name, const char* in_type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, out_type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = (");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)out_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ")");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, in_type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_load_constant_0(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_array_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t out_index, int32_t array_index, int32_t index_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, element_type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "(*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[index]; \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_array_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t array_index, int32_t index_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "(*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[index] \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, element_type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t out_index, int32_t array_index, int32_t index_index, int32_t unit) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  {
    int32_t offset;
    for (offset = 0; offset < unit; offset++) {
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "        ");
      SPVM_CSOURCE_BUILDER_add_operand_offset(compiler, string_buffer, element_type_name, out_index, offset);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "(*(");
      SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[");
      SPVM_STRING_BUFFER_add_int(compiler, string_buffer , unit);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , " * index + ");
      SPVM_STRING_BUFFER_add_int(compiler, string_buffer , offset);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "]; \n");
    }
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t out_index, int32_t array_index, int32_t index_index, int32_t unit, int32_t offset) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, element_type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " =");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "(*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , unit);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " * index + ");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , offset);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "]; \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_value_t_array_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t array_index, int32_t index_index, int32_t in_index, int32_t unit) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  
  {
    int32_t offset;
    for (offset = 0; offset < unit; offset++) {
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "      (*(");
      SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[");
      SPVM_STRING_BUFFER_add_int(compiler, string_buffer , unit);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , " * index + ");
      SPVM_STRING_BUFFER_add_int(compiler, string_buffer , offset);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
      SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
      SPVM_CSOURCE_BUILDER_add_operand_offset(compiler, string_buffer, element_type_name, in_index, offset);
      SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
    }
  }

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* element_type_name, int32_t array_index, int32_t index_index, int32_t in_index, int32_t unit, int32_t offset) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", array_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", index_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "        (*(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)element_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "**)&(*(void**)array))[");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , unit);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " * index + ");
  SPVM_STRING_BUFFER_add_int(compiler, string_buffer , offset);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, element_type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
}

void SPVM_CSOURCE_BUILDER_add_move(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* type_name, int32_t out_index, int32_t in_index) {
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
}

void SPVM_CSOURCE_BUILDER_add_get_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t out_index, int32_t object_index, SPVM_OP* op_field_access) {
  SPVM_FIELD* field = op_field_access->uv.field_access->field;
  const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
  const char* field_name = field->op_name->uv.name;

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", object_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, field_type_name, out_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " = *(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)&fields[");
  SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
}

void SPVM_CSOURCE_BUILDER_add_set_field(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* field_type_name, int32_t object_index, SPVM_OP* op_field_access, int32_t in_index) {
  SPVM_FIELD* field = op_field_access->uv.field_access->field;
  const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
  const char* field_name = field->op_name->uv.name;

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", object_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(object == NULL, 0)) {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "      *(");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_type_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)&fields[");
  SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "] = ");
  SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, field_type_name, in_index);
  SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
}

void SPVM_CSOURCE_BUILDER_build_package_csource(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name) {
  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, package_name, strlen(package_name));
  
  assert(op_package);
  
  SPVM_PACKAGE* package = op_package->uv.package;
  SPVM_LIST* op_subs = package->op_subs;
  
  // Head part - include and define
  SPVM_CSOURCE_BUILDER_build_head(compiler, string_buffer);
  
  // Subroutine decrations
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "// Function Declarations\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      const char* sub_name = sub->op_name->uv.name;
      if (sub->have_precompile_desc) {
        SPVM_CSOURCE_BUILDER_build_sub_declaration(compiler, string_buffer, package_name, sub_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
      }
    }
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  
  // Subroutine implementations
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "// Function Implementations\n");
  {
    int32_t sub_index;
    for (sub_index = 0; sub_index < op_subs->length; sub_index++) {
      SPVM_OP* op_sub = SPVM_LIST_fetch(op_subs, sub_index);
      SPVM_SUB* sub = op_sub->uv.sub;
      const char* sub_name = sub->op_name->uv.name;
      if (sub->have_precompile_desc) {
        SPVM_CSOURCE_BUILDER_build_sub_implementation(compiler, string_buffer, package_name, sub_name);
      }
    }
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
}

void SPVM_CSOURCE_BUILDER_build_head(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer) {
  (void)compiler;
  
  // Include header
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#ifndef SPVM_CSOURCE_BUILDER_H\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_CSOURCE_BUILDER_H\n");
  
  // API header
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <spvm_native.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <spvm_core_func.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  
  // Inline macro function
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <stdlib.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <string.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <stdio.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <inttypes.h>\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#include <math.h>\n");

  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset)))\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))++)\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_INC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "do {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(object);\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object) ((*(int32_t*)((intptr_t)object + (intptr_t)env->object_ref_count_byte_offset))--)\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT(object)\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "do {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(object) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(object); }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { env->dec_ref_count(env, object); }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_ISWEAK(object) ((intptr_t)object & 1)\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#define SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(dist_ptr, source) \\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "do {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  void* tmp_object = source;\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (tmp_object != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(tmp_object);\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (*(void**)(dist_ptr) != NULL) {\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (SPVM_RUNTIME_C_INLINE_ISWEAK(*(void**)(dist_ptr))) { env->unweaken(env, dist_ptr); }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)(dist_ptr)) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)(dist_ptr)); }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { env->dec_ref_count(env, *(void**)(dist_ptr)); }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  *(void**)(dist_ptr) = tmp_object;\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "} while (0)\\\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "#endif\n");
}

void SPVM_CSOURCE_BUILDER_build_sub_declaration(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, package_name, strlen(package_name));
  SPVM_PACKAGE* package = op_package->uv.package;
  SPVM_OP* op_sub = SPVM_HASH_fetch(package->op_sub_symtable, sub_name, strlen(sub_name));
  SPVM_SUB* sub = op_sub->uv.sub;

  assert(sub->have_precompile_desc);
  
  // Subroutine name
  const char* sub_abs_name = sub->abs_name;
  
  // Return type
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "int32_t ");
        
  // Subroutine name. Replace : to _
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "SPVM_PRECOMPILE_");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_abs_name);
  {
    int32_t index = string_buffer->length - strlen(sub_abs_name);
    
    while (index < string_buffer->length) {
      if (string_buffer->buffer[index] == ':') {
        string_buffer->buffer[index] = '_';
      }
      index++;
    }
  }
  
  // Arguments
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "(SPVM_ENV* env, SPVM_VALUE* stack)");
}

void SPVM_CSOURCE_BUILDER_build_sub_implementation(SPVM_COMPILER* compiler, SPVM_STRING_BUFFER* string_buffer, const char* package_name, const char* sub_name) {
  SPVM_OP* op_package = SPVM_HASH_fetch(compiler->op_package_symtable, package_name, strlen(package_name));
  SPVM_PACKAGE* package = op_package->uv.package;
  SPVM_OP* op_sub = SPVM_HASH_fetch(package->op_sub_symtable, sub_name, strlen(sub_name));
  SPVM_SUB* sub = op_sub->uv.sub;
  
  // Subroutine return type
  SPVM_TYPE* sub_return_type = sub->op_return_type->uv.type;
  
  int32_t sub_return_basic_type_id = sub_return_type->basic_type->id;
  
  int32_t sub_return_type_dimension = sub_return_type->dimension;
  int32_t sub_return_type_is_value_type = SPVM_TYPE_is_value_type(compiler, sub_return_type);
  int32_t sub_return_type_is_object_type = SPVM_TYPE_is_object_type(compiler, sub_return_type);

  int32_t sub_return_type_width = SPVM_TYPE_get_width(compiler, sub_return_type);
  
  assert(sub->have_precompile_desc);
  
  SPVM_CSOURCE_BUILDER_build_sub_declaration(compiler, string_buffer, sub->op_package->uv.package->op_name->uv.name, sub->op_name->uv.name);

  // Block start
  SPVM_STRING_BUFFER_add(compiler, string_buffer , " {\n");
  
  if (sub->mortal_stack_max > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t mortal_stack[");
    SPVM_STRING_BUFFER_add_int(compiler, string_buffer , sub->mortal_stack_max);
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t mortal_stack_top = 0;\n");
  }
  
  // Call subroutine argument stack top
  int32_t call_sub_arg_stack_top = 0;

  // Condition flag
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  register int32_t condition_flag;\n");
  
  // Convert string
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  char convert_string[30];\n");

  // Exception
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t exception_flag = 0;\n");

  int32_t arg_alloc_length = SPVM_SUB_get_arg_alloc_length(compiler, sub);

  int32_t var_alloc_length = SPVM_SUB_get_var_alloc_length(compiler, sub);
  
  // Variable declaration
  if (sub->op_mys->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_VALUE vars[");
    SPVM_STRING_BUFFER_add_int(compiler, string_buffer , var_alloc_length);
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
  }
  
  // Initialize variables with type information
  if (sub->op_mys->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Initialize variables\n");
  }
  {
    int32_t my_index;
    for (my_index = 0; my_index < sub->op_mys->length; my_index++) {
      SPVM_OP* op_my = SPVM_LIST_fetch(sub->op_mys, my_index);
      SPVM_MY* my = op_my->uv.my;
      SPVM_TYPE* my_type = op_my->uv.my->op_type->uv.type;
      _Bool my_type_is_value_t = SPVM_TYPE_is_value_type(compiler, my_type);
      _Bool my_type_is_object_type = SPVM_TYPE_is_object_type(compiler, my_type);
      
      // Value type
      if (my_type_is_value_t) {
        SPVM_OP* op_package = my_type->basic_type->op_package;
        assert(op_package);
        
        SPVM_OP* op_first_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, 0);
        assert(op_first_field);
        
        SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_first_field);
        assert(field_type->dimension == 0);

        for (int32_t offset = 0; offset < op_package->uv.package->op_fields->length; offset++) {
          switch (field_type->basic_type->id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
              break;
            }
            default:
              assert(0);
          }
        }
      }
      // Object type
      else if (my_type_is_object_type) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = NULL;\n");
      }
      // Numeric type
      else {
        switch (my_type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", my->var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = 0;\n");
            break;
          }
          default:
            assert(0);
        }
      }
    }
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  }
  
  // Copy arguments to variables with type information
  if (sub->op_args->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Copy arguments to variables\n");
  }
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_MY* arg_my = op_arg->uv.my;
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      _Bool arg_type_is_value_t = SPVM_TYPE_is_value_type(compiler, arg_type);
      _Bool arg_type_is_object_type = SPVM_TYPE_is_object_type(compiler, arg_type);
      
      // Value type
      if (arg_type_is_value_t) {
        SPVM_OP* op_package = arg_type->basic_type->op_package;
        assert(op_package);
        
        SPVM_OP* op_first_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, 0);
        assert(op_first_field);
        
        SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_first_field);
        assert(field_type->dimension == 0);

        for (int32_t offset = 0; offset < op_package->uv.package->op_fields->length; offset++) {
          switch (field_type->basic_type->id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", arg_my->var_id + offset);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            default:
              assert(0);
          }
        }
      }
      // Object type
      else if (arg_type_is_object_type) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", arg_my->var_id);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "void*", arg_my->var_id);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
      }
      // Numeric type
      else {
        switch (arg_type->basic_type->id) {
          case SPVM_BASIC_TYPE_C_ID_BYTE: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_SHORT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_INT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_LONG: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_FLOAT: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            break;
          }
          case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
            SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", arg_my->var_id);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
            break;
          }
          default:
            assert(0);
        }
      }
    }
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  }
  
  // If arg is object, increment reference count
  {
    int32_t arg_index;
    for (arg_index = 0; arg_index < sub->op_args->length; arg_index++) {
      SPVM_OP* op_arg = SPVM_LIST_fetch(sub->op_args, arg_index);
      SPVM_TYPE* arg_type = op_arg->uv.my->op_type->uv.type;
      _Bool arg_type_is_value_t = SPVM_TYPE_is_value_type(compiler, arg_type);
      
      if (SPVM_TYPE_is_object_type(compiler, arg_type) && !arg_type_is_value_t) {
        SPVM_MY* my_arg = op_arg->uv.my;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", my_arg->var_id);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " != NULL) { SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", my_arg->var_id);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "); }\n");
      }
    }
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
  }
  
  // Get field index
  if (sub->op_field_accesses->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Get field index\n");
  }
  {
    SPVM_HASH* field_abs_name_symtable = SPVM_HASH_new(1);
    int32_t field_access_index;
    for (field_access_index = 0; field_access_index < sub->op_field_accesses->length; field_access_index++) {
      SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, field_access_index);
      SPVM_FIELD* field = op_field_access->uv.field_access->field;
      const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
      const char* field_signature = field->signature;
      const char* field_name = field->op_name->uv.name;
      
      SPVM_FIELD* found_field = SPVM_HASH_fetch(field_abs_name_symtable, field->abs_name, strlen(field->abs_name));
      if (!found_field) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t ");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = env->get_field_index(env, \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\");\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " < 0) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* exception = env->new_string_raw(env, \"Field not found ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)field_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", 0);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        SPVM_HASH_insert(field_abs_name_symtable, field->abs_name, strlen(field->abs_name), field);
      }
    }
    SPVM_HASH_free(field_abs_name_symtable);
  }
  
  // Get package variable id
  if (sub->op_package_var_accesses->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Get package variable id\n");
  }
  {
    SPVM_HASH* package_var_abs_name_symtable = SPVM_HASH_new(1);
    int32_t package_var_access_index;
    for (package_var_access_index = 0; package_var_access_index < sub->op_package_var_accesses->length; package_var_access_index++) {
      SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, package_var_access_index);
      SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
      const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
      const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;
      const char* package_var_signature = package_var->signature;
      
      SPVM_PACKAGE_VAR* found_package_var = SPVM_HASH_fetch(package_var_abs_name_symtable, package_var->abs_name, strlen(package_var->abs_name));
      if (!found_package_var) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t ");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = env->get_package_var_id(env, \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\");\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " < 0) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* exception = env->new_string_raw(env, \"Package variable not found ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_var_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_var_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", 0);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        SPVM_HASH_insert(package_var_abs_name_symtable, package_var->abs_name, strlen(package_var->abs_name), package_var);
      }
    }
    SPVM_HASH_free(package_var_abs_name_symtable);
  }

  // Get sub id
  if (sub->op_call_subs->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Get sub id\n");
  }
  {
    SPVM_HASH* sub_abs_name_symtable = SPVM_HASH_new(1);
    int32_t call_sub_index;
    for (call_sub_index = 0; call_sub_index < sub->op_call_subs->length; call_sub_index++) {
      SPVM_OP* op_call_sub = SPVM_LIST_fetch(sub->op_call_subs, call_sub_index);
      SPVM_SUB* sub = op_call_sub->uv.call_sub->sub;
      const char* sub_package_name = sub->op_package->uv.package->op_name->uv.name;
      const char* sub_signature = sub->signature;
      const char* sub_name = sub->op_name->uv.name;
      
      SPVM_FIELD* found_sub = SPVM_HASH_fetch(sub_abs_name_symtable, sub->abs_name, strlen(sub->abs_name));
      if (!found_sub) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t ");
        SPVM_STRING_BUFFER_add_sub_id_name(compiler, string_buffer , sub_package_name, sub_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = env->get_sub_id(env, \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\");\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_STRING_BUFFER_add_sub_id_name(compiler, string_buffer , sub_package_name, sub_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " < 0) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* exception = env->new_string_raw(env, \"Subroutine not found ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_signature);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", 0);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        SPVM_HASH_insert(sub_abs_name_symtable, sub->abs_name, strlen(sub->abs_name), sub);
      }
    }
    SPVM_HASH_free(sub_abs_name_symtable);
  }

  // Get basic type id
  if (sub->op_types->length > 0) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // Get basic type id\n");
  }
  {
    SPVM_HASH* basic_type_symtable = SPVM_HASH_new(1);
    int32_t type_index;
    for (type_index = 0; type_index < sub->op_types->length; type_index++) {
      SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, type_index);
      SPVM_BASIC_TYPE* basic_type = op_type->uv.type->basic_type;
      const char* basic_type_name = basic_type->name;
      
      SPVM_BASIC_TYPE* found_basic_type = SPVM_HASH_fetch(basic_type_symtable, basic_type_name, strlen(basic_type_name));
      if (!found_basic_type) {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  int32_t ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = env->get_basic_type_id(env, \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\");\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " < 0) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* exception = env->new_string_raw(env, \"Basic type not found ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", 0);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    return SPVM_EXCEPTION;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        SPVM_HASH_insert(basic_type_symtable, basic_type_name, strlen(basic_type_name), basic_type);
      }
    }
    SPVM_HASH_free(basic_type_symtable);
  }
  
  SPVM_OPCODE* opcodes = compiler->opcode_array->values;
  int32_t sub_opcode_base = sub->opcode_base;
  int32_t opcode_length = sub->opcode_length;
  int32_t opcode_index = 0;
  
  SPVM_OPCODE* opcode = NULL;

  while (opcode_index < opcode_length) {

    // Line label
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "L");
    SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode_index);
    SPVM_STRING_BUFFER_add(compiler, string_buffer , ": ");
    
    opcode = &(opcodes[sub_opcode_base + opcode_index]);

    SPVM_STRING_BUFFER_add(compiler, string_buffer , "// ");
    SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)SPVM_OPCODE_C_ID_NAMES[opcode->id]);
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");

    
    switch (opcode->id) {
      case SPVM_OPCODE_C_ID_BOOL_INT:
        SPVM_CSOURCE_BUILDER_add_bool(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_LONG:
        SPVM_CSOURCE_BUILDER_add_bool(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_FLOAT:
        SPVM_CSOURCE_BUILDER_add_bool(compiler, string_buffer , "float", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_bool(compiler, string_buffer , "double", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_BOOL_OBJECT:
        SPVM_CSOURCE_BUILDER_add_bool(compiler, string_buffer , "void*", opcode->operand0);
        break;
      case SPVM_OPCODE_C_ID_IS_UNDEF:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " == NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_IS_NOT_UNDEF:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  condition_flag = (");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " != NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_EQ_INT:
        SPVM_CSOURCE_BUILDER_add_eq(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_LONG:
        SPVM_CSOURCE_BUILDER_add_eq(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_FLOAT:
        SPVM_CSOURCE_BUILDER_add_eq(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_eq(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_EQ_OBJECT:
        SPVM_CSOURCE_BUILDER_add_eq(compiler, string_buffer , "void*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_INT:
        SPVM_CSOURCE_BUILDER_add_ne(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_LONG:
        SPVM_CSOURCE_BUILDER_add_ne(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_ne(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_ne(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NE_OBJECT:
        SPVM_CSOURCE_BUILDER_add_ne(compiler, string_buffer , "void*", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_INT:
        SPVM_CSOURCE_BUILDER_add_gt(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_LONG:
        SPVM_CSOURCE_BUILDER_add_gt(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_FLOAT:
        SPVM_CSOURCE_BUILDER_add_gt(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GT_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_gt(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_INT:
        SPVM_CSOURCE_BUILDER_add_ge(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_LONG:
        SPVM_CSOURCE_BUILDER_add_ge(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_ge(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_GE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_ge(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_INT:
        SPVM_CSOURCE_BUILDER_add_lt(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_LONG:
        SPVM_CSOURCE_BUILDER_add_lt(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_FLOAT:
        SPVM_CSOURCE_BUILDER_add_lt(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LT_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_lt(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_INT:
        SPVM_CSOURCE_BUILDER_add_le(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_LONG:
        SPVM_CSOURCE_BUILDER_add_le(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_le(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_LE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_le(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_ISA:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* basic_type_name = op_type->uv.type->basic_type->name;
        int32_t dimension = op_type->uv.type->dimension;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t dimension = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , dimension);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (*(int32_t*)(object + (intptr_t)env->object_basic_type_id_byte_offset) == basic_type_id && *(int32_t*)(object + (intptr_t)env->object_dimension_byte_offset) == dimension);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_STRING_EQ:
      case SPVM_OPCODE_C_ID_STRING_NE:
      case SPVM_OPCODE_C_ID_STRING_GT:
      case SPVM_OPCODE_C_ID_STRING_GE:
      case SPVM_OPCODE_C_ID_STRING_LT:
      case SPVM_OPCODE_C_ID_STRING_LE:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object1 = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object2 = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t length1 = *(SPVM_VALUE_int*)((intptr_t)object1 + (intptr_t)env->object_elements_length_byte_offset);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t lenght2 = *(SPVM_VALUE_int*)((intptr_t)object2 + (intptr_t)env->object_elements_length_byte_offset);\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_VALUE_byte* bytes1 = *(SPVM_VALUE_byte**)&(*(void**)object1);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_VALUE_byte* bytes2 = *(SPVM_VALUE_byte**)&(*(void**)object2);\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t short_string_length = length1 < lenght2 ? length1 : lenght2;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t retval = memcmp(bytes1, bytes2, short_string_length);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t cmp;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (retval) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      cmp = retval < 0 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } else if (length1 == lenght2) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      cmp = 0;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      cmp = length1 < lenght2 ? -1 : 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_STRING_EQ:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp == 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_NE:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp != 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_GT:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp == 1);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_GE:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp >= 0);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_LT:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp == -1);\n");
            break;
          case SPVM_OPCODE_C_ID_STRING_LE:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    condition_flag = (cmp <= 0);\n");
            break;
        }
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_ADD_INT:
        SPVM_CSOURCE_BUILDER_add_add(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_LONG:
        SPVM_CSOURCE_BUILDER_add_add(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_FLOAT:
        SPVM_CSOURCE_BUILDER_add_add(compiler, string_buffer , "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ADD_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_add(compiler, string_buffer , "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_INT:
        SPVM_CSOURCE_BUILDER_add_subtract(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_LONG:
        SPVM_CSOURCE_BUILDER_add_subtract(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_FLOAT:
        SPVM_CSOURCE_BUILDER_add_subtract(compiler, string_buffer , "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_subtract(compiler, string_buffer , "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_INT:
        SPVM_CSOURCE_BUILDER_add_multiply(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_LONG:
        SPVM_CSOURCE_BUILDER_add_multiply(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_FLOAT:
        SPVM_CSOURCE_BUILDER_add_multiply(compiler, string_buffer , "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_multiply(compiler, string_buffer , "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_INT:
        SPVM_CSOURCE_BUILDER_add_divide_integral(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_LONG: 
        SPVM_CSOURCE_BUILDER_add_divide_integral(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_divide_floating_point(compiler, string_buffer , "float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_DIVIDE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_divide_floating_point(compiler, string_buffer , "double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_INT:
        SPVM_CSOURCE_BUILDER_add_remainder_integral(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_LONG: 
        SPVM_CSOURCE_BUILDER_add_remainder_integral(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_FLOAT:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "float", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = (float)fmod((double)");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "float", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", (double)");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "float", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        break;
      case SPVM_OPCODE_C_ID_REMAINDER_DOUBLE:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "double", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = fmod(");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "double", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "double", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_add_left_shift(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_add_left_shift(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_INT:
        SPVM_CSOURCE_BUILDER_add_right_shift(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_LONG:
        SPVM_CSOURCE_BUILDER_add_right_shift(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_INT:
        SPVM_CSOURCE_BUILDER_add_right_shift_unsigned(compiler, string_buffer , "int32_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_RIGHT_SHIFT_UNSIGNED_LONG:
        SPVM_CSOURCE_BUILDER_add_right_shift_unsigned(compiler, string_buffer , "int64_t", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_INT:
        SPVM_CSOURCE_BUILDER_add_bit_and(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_AND_LONG:
        SPVM_CSOURCE_BUILDER_add_bit_and(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_INT:
        SPVM_CSOURCE_BUILDER_add_bit_or(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_OR_LONG:
        SPVM_CSOURCE_BUILDER_add_bit_or(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_INT:
        SPVM_CSOURCE_BUILDER_add_bit_xor(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_BIT_XOR_LONG:
        SPVM_CSOURCE_BUILDER_add_bit_xor(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_INT:
        SPVM_CSOURCE_BUILDER_add_negate(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_LONG:
        SPVM_CSOURCE_BUILDER_add_negate(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_negate(compiler, string_buffer , "float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_NEGATE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_negate(compiler, string_buffer , "double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_INT:
        SPVM_CSOURCE_BUILDER_add_complement(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_COMPLEMENT_LONG:
        SPVM_CSOURCE_BUILDER_add_complement(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_BYTE:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_SHORT:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_INT:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_LONG:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_FLOAT:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_INC_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_inc(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, (int16_t)opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_BYTE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_byte", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_SHORT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_short", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_INT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_int", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_LONG:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_long", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_FLOAT:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_float", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_convert(compiler, string_buffer , "SPVM_VALUE_double", "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;

      case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
      case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_CONVERT_BYTE_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%\" PRId8, ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_SHORT_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%\" PRId16, ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_INT_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%\" PRId32, ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_LONG_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%\" PRId64, ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            break;
          case SPVM_OPCODE_C_ID_CONVERT_FLOAT_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%g\", ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            
            break;
          case SPVM_OPCODE_C_ID_CONVERT_DOUBLE_TO_STRING:
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    sprintf(convert_string, \"%g\", ");
            SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", opcode->operand1);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
            break;
        }
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t string_length = strlen(convert_string);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* string = env->new_string_raw(env, convert_string, string_length);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", string);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_BYTE: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_byte(compiler, string_buffer , *(SPVM_VALUE_byte*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_SHORT: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_short(compiler, string_buffer , *(SPVM_VALUE_short*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_INT: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , *(SPVM_VALUE_int*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_LONG: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_constant = SPVM_LIST_fetch(sub->op_constants, rel_id);
        SPVM_VALUE_long value = *(SPVM_VALUE_long*)&op_constant->uv.constant->value;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_long(compiler, string_buffer , value);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "ULL;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_FLOAT: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_float(compiler, string_buffer , *(SPVM_VALUE_float*)&opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "f;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_CONSTANT_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_constant = SPVM_LIST_fetch(sub->op_constants, rel_id);
        SPVM_VALUE_double value = *(SPVM_VALUE_double*)&op_constant->uv.constant->value;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_STRING_BUFFER_add_double(compiler, string_buffer , value);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_BYTE:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_SHORT:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_INT:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_LONG:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_FLOAT:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_array_fetch(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_BYTE: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_SHORT: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_INT: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_LONG: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_FLOAT: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FETCH_DOUBLE: {
        SPVM_CSOURCE_BUILDER_add_value_t_array_fetch(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_BYTE: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_SHORT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_INT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_LONG: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_FLOAT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_FETCH_DOUBLE: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_fetch(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_FETCH_OBJECT:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        void* object = (*(SPVM_VALUE_object**)&(*(void**)array))[index];\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", object); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  } \n");
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_array_store(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2);
        break;
      case SPVM_OPCODE_C_ID_ARRAY_STORE_OBJECT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(array == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(index < 0 || index >= *(int32_t*)((intptr_t)array + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "          env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "          exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "          object_address, ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        );\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }");
        
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_STORE_UNDEF:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* array = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t index = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " == NULL, 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Array must not be undef\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      if (__builtin_expect(");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " < 0 || ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  >= *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " + (intptr_t)env->object_elements_length_byte_offset), 0)) { \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        env->set_exception(env, env->new_string_raw(env, \"Index is out of range\", 0)); \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      } \n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        void* object_address = &((*(SPVM_VALUE_object**)&(*(void**)array))[index]);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "          object_address,\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "          NULL");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "        );\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }");
        
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_BYTE:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_SHORT:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_INT:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_LONG:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_STORE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_value_t_array_store(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2, opcode->operand3);
        break;
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_BYTE: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_SHORT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_INT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_LONG: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_FLOAT: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_VALUE_T_ARRAY_FIELD_STORE_DOUBLE: {
        int32_t unit = opcode->operand3 & 0xF;
        int32_t offset = opcode->operand3 >> 4;
        SPVM_CSOURCE_BUILDER_add_value_t_array_field_store(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, opcode->operand2, unit, offset);
        break;
      }
      case SPVM_OPCODE_C_ID_MOVE_BYTE:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_SHORT:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_INT:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_LONG:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_FLOAT:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_DOUBLE:
        SPVM_CSOURCE_BUILDER_add_move(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1);
        break;
      case SPVM_OPCODE_C_ID_MOVE_OBJECT:
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
          SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        break;
      case SPVM_OPCODE_C_ID_MOVE_UNDEF:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", NULL);\n");
        break;
      case SPVM_OPCODE_C_ID_PUSH_MORTAL: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  mortal_stack[mortal_stack_top] = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  mortal_stack_top++;\n");
        break;
      }

      case SPVM_OPCODE_C_ID_LEAVE_SCOPE: {
        int32_t original_mortal_stack_top = opcode->operand0;
        if (sub->mortal_stack_max > 0) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t original_mortal_stack_top = ");
          SPVM_STRING_BUFFER_add_int(compiler, string_buffer , original_mortal_stack_top);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    {\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      int32_t mortal_stack_index;\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      for (mortal_stack_index = original_mortal_stack_top; mortal_stack_index < mortal_stack_top; mortal_stack_index++) {\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "        int32_t var_index = mortal_stack[mortal_stack_index];\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "        if (*(void**)&vars[var_index] != NULL) {\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "          if (SPVM_RUNTIME_C_INLINE_GET_REF_COUNT(*(void**)&vars[var_index]) > 1) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(*(void**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "          else { env->dec_ref_count(env, *(void**)&vars[var_index]); }\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "          *(void**)&vars[var_index] = NULL;\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "        }\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      }\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    mortal_stack_top = original_mortal_stack_top;\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        }
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* basic_type_name = op_type->uv.type->basic_type->name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = env->new_object_raw(env, basic_type_id);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", object);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");

        break;
      }
      case SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_byte_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_short_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_INT_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_int_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_LONG_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_long_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_float_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY:
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_double_array_raw(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      case SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* basic_type_name = op_type->uv.type->basic_type->name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", env->new_object_array_raw(env, basic_type_id, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* basic_type_name = op_type->uv.type->basic_type->name;
        int32_t element_dimension = op_type->uv.type->dimension - 1;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t element_dimension = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , element_dimension);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", env->new_multi_array_raw(env, basic_type_id, element_dimension, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_VALUE_T_ARRAY: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* basic_type_name = op_type->uv.type->basic_type->name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", env->new_value_t_array_raw(env, basic_type_id, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_NEW_STRING: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_constant = SPVM_LIST_fetch(sub->op_constants, rel_id);
        SPVM_CONSTANT* constant = op_constant->uv.constant;

        const char* name = constant->value.oval;
        int32_t length = constant->string_length;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "env->new_string_raw(env, \"");
        
        {
          int32_t i;
          for (i = 0; i < length; i++) {
            SPVM_STRING_BUFFER_add_hex_char(compiler, string_buffer , name[i]);
          }
        }
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , length);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_ARRAY_LENGTH: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " == NULL) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, env->new_string_raw(env, \"Can't get array length of undef value.\", 0));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = *(int32_t*)((intptr_t)");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " + (intptr_t)env->object_elements_length_byte_offset);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_INT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_LONG: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_get_field(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, opcode->operand1, op_field_access);
        break;
      }
      case SPVM_OPCODE_C_ID_GET_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);
        SPVM_FIELD* field = op_field_access->uv.field_access->field;
        const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
        const char* field_name = field->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      void* object_field = *(SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", object_field);");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_BYTE: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_byte", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_SHORT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_short", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_INT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);
        
        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_int", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_LONG: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_long", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_FLOAT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_float", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);

        SPVM_CSOURCE_BUILDER_add_set_field(compiler, string_buffer , "SPVM_VALUE_double", opcode->operand0, op_field_access, opcode->operand2);
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_OBJECT:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);
        SPVM_FIELD* field = op_field_access->uv.field_access->field;
        const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
        const char* field_name = field->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      void* object_field_address = (SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "object_field_address,");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    );\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_FIELD_UNDEF:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);
        SPVM_FIELD* field = op_field_access->uv.field_access->field;
        const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
        const char* field_name = field->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (__builtin_expect(object == NULL, 0)) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, env->new_string_raw(env, \"Object must be not undef.\", 0));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_VALUE* fields = *(SPVM_VALUE**)&(*(void**)object);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      void* object_field_address = (SPVM_VALUE_object*)&fields[");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(object_field_address, NULL);");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_WEAKEN_FIELD_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_field_access = SPVM_LIST_fetch(sub->op_field_accesses, rel_id);
        SPVM_FIELD* field = op_field_access->uv.field_access->field;
        const char* field_package_name = field->op_package->uv.package->op_name->uv.name;
        const char* field_name = field->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = env->weaken_object_field(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_STRING_BUFFER_add_field_index_name(compiler, string_buffer , field_package_name, field_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CONCAT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* concat_string = env->concat(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand2);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (concat_string == NULL) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    &");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", concat_string);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GOTO: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_EQ_ZERO: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (condition_flag == 0) { goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_IF_NE_ZERO: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (condition_flag) { goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "; }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", env->get_exception(env));\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  env->set_exception(env, ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  env->set_exception(env, NULL);\n");
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE:
      {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, rel_id);
        SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
        const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
        const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;

        char* package_var_access_type = NULL;
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_BYTE:
            package_var_access_type = "SPVM_VALUE_byte";
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_SHORT:
            package_var_access_type = "SPVM_VALUE_short";
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_INT:
            package_var_access_type = "SPVM_VALUE_int";
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_LONG:
            package_var_access_type = "SPVM_VALUE_long";
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_FLOAT:
            package_var_access_type = "float";
            break;
          case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_DOUBLE:
            package_var_access_type = "double";
            break;
        }
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, package_var_access_type, opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = *(");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , package_var_access_type);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_GET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, rel_id);
        SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
        const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
        const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", *(void**)");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "]);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT:
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE:
      {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, rel_id);
        SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
        const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
        const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;

        char* package_var_access_type = NULL;
        switch (opcode->id) {
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_BYTE:
            package_var_access_type = "SPVM_VALUE_byte";
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_SHORT:
            package_var_access_type = "SPVM_VALUE_short";
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_INT:
            package_var_access_type = "SPVM_VALUE_int";
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_LONG:
            package_var_access_type = "SPVM_VALUE_long";
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_FLOAT:
            package_var_access_type = "float";
            break;
          case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_DOUBLE:
            package_var_access_type = "double";
            break;
        }
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    *(");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , package_var_access_type);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "*)");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "]");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, package_var_access_type, opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_OBJECT: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, rel_id);
        SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
        const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
        const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "],\n");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ");");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_SET_PACKAGE_VAR_UNDEF: {
        int32_t rel_id = opcode->operand0;
        SPVM_OP* op_package_var_access = SPVM_LIST_fetch(sub->op_package_var_accesses, rel_id);
        SPVM_PACKAGE_VAR* package_var = op_package_var_access->uv.package_var_access->op_package_var->uv.package_var;
        const char* package_var_package_name = package_var->op_package->uv.package->op_name->uv.name;
        const char* package_var_name = package_var->op_var->uv.var->op_name->uv.name;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN((void**)&(*(SPVM_VALUE**)(env->get_runtime(env) + (intptr_t)env->runtime_package_vars_byte_offset))[");
        SPVM_STRING_BUFFER_add_package_var_id_name(compiler, string_buffer , package_var_package_name, package_var_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "], NULL);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_BYTE:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_SHORT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_INT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_LONG:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_object", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_object", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        call_sub_arg_stack_top++;
        break;
      }
      case SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
        SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_object", call_sub_arg_stack_top);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , " = NULL;\n");
        call_sub_arg_stack_top++;
        
        break;
      }
      case SPVM_OPCODE_C_ID_CAST: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_type = SPVM_LIST_fetch(sub->op_types, rel_id);
        const char* cast_basic_type_name = op_type->uv.type->basic_type->name;
        int32_t cast_type_dimension = op_type->uv.type->dimension;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t cast_basic_type_id = ");
        SPVM_STRING_BUFFER_add_basic_type_id_name(compiler, string_buffer , cast_basic_type_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t cast_type_dimension = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , cast_type_dimension);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t can_cast = env->check_cast(env, cast_basic_type_id, cast_type_dimension, object);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (can_cast) { SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ", object); }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    else {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      void* exception = env->new_string_raw(env, \"Can't cast uncompatible type.\", 0);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, exception);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "      exception_flag = 1;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_CALL_SUB:
      case SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD:
      {
        int32_t var_id = opcode->operand0;
        int32_t rel_id = opcode->operand1;
        SPVM_OP* op_call_sub = SPVM_LIST_fetch(sub->op_call_subs, rel_id);
        int32_t decl_sub_id = op_call_sub->uv.call_sub->sub->id;

        SPVM_OP* op_sub_decl = SPVM_LIST_fetch(compiler->op_subs, decl_sub_id);
        SPVM_SUB* decl_sub = op_sub_decl->uv.sub;
        
        // Declare subroutine return type
        SPVM_TYPE* decl_sub_return_type = decl_sub->op_return_type->uv.type;
        int32_t decl_sub_return_type_is_object = SPVM_TYPE_is_object_type(compiler, decl_sub_return_type);
        int32_t decl_sub_return_type_is_value_type = SPVM_TYPE_is_value_type(compiler, decl_sub_return_type);
        
        // Declare subroutine return type id
        int32_t decl_sub_return_basic_type_id = decl_sub_return_type->basic_type->id;
        int32_t decl_sub_return_type_dimension = decl_sub_return_type->dimension;
        
        // Declare subroutine argument length
        int32_t decl_sub_args_length = decl_sub->op_args->length;

        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  // ");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->abs_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  {\n");
        
        // Call subroutine id
        if (opcode->id == SPVM_OPCODE_C_ID_CALL_SUB) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t call_sub_id = ");
          SPVM_STRING_BUFFER_add_sub_id_name(compiler, string_buffer , decl_sub->op_package->uv.package->op_name->uv.name, decl_sub->op_name->uv.name);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        }
        else if (opcode->id == SPVM_OPCODE_C_ID_CALL_INTERFACE_METHOD) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    void* object = *(void**)&vars[");
          SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand2);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "];\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t call_sub_id = env->get_sub_id_method_call(env, object, \"");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->signature);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "\");\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (call_sub_id < 0) {\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      void* exception = env->new_string_raw(env, \"Subroutine not found ");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->op_package->uv.package->op_name->uv.name);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , " ");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->signature);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "\", 0);\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      env->set_exception(env, exception);\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "      return SPVM_EXCEPTION;\n");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        }
        else {
          assert(0);
        }


        // Subroutine inline expantion in same package
        if (decl_sub->op_package->uv.package->id == sub->op_package->uv.package->id && decl_sub->have_precompile_desc) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = SPVM_PRECOMPILE_");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->abs_name);
          {
            int32_t index = string_buffer->length - strlen(decl_sub->abs_name);
            
            while (index < string_buffer->length) {
              if (string_buffer->buffer[index] == ':') {
                string_buffer->buffer[index] = '_';
              }
              index++;
            }
          }
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "(env, stack);\n");
        }
        // Inline expansion is done in native core function
        else if (strcmp(decl_sub->op_package->uv.package->op_name->uv.name, "SPVM::CORE") == 0 && decl_sub->have_native_desc) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = SPVM_CORE_FUNC_");
          SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)decl_sub->op_name->uv.name);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "(env, stack);\n");
        }
        // Call subroutine
        else {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = env->call_sub(env, call_sub_id, stack);\n");
        }
        
        // Call subroutine
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (!exception_flag) {\n");
        if (decl_sub_return_type_is_value_type) {
          SPVM_OP* op_package = decl_sub_return_type->basic_type->op_package;
          assert(op_package);
          
          SPVM_OP* op_first_field = SPVM_LIST_fetch(op_package->uv.package->op_fields, 0);
          assert(op_first_field);
          
          SPVM_TYPE* field_type = SPVM_OP_get_type(compiler, op_first_field);
          assert(field_type->dimension == 0);

          for (int32_t offset = 0; offset < op_package->uv.package->op_fields->length; offset++) {
            switch (field_type->basic_type->id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              default:
                assert(0);
            }
          }
        }
        else if (decl_sub_return_type_is_object) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , " SPVM_RUNTIME_C_INLINE_OBJECT_ASSIGN(&");
          SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", var_id);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ", stack[0].oval);");
        }
        else if ((decl_sub_return_type_dimension == 0 && decl_sub_return_basic_type_id != SPVM_BASIC_TYPE_C_ID_VOID)) {
          switch (decl_sub_return_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "      ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            default:
              assert(0);
          }
        }
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    }\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");

        call_sub_arg_stack_top -=  decl_sub_args_length;
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_CATCH: {
        SPVM_OP* op_sub = SPVM_LIST_fetch(package->op_subs, opcode->operand1);
        SPVM_SUB* sub = op_sub->uv.sub;
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = op_sub->line + rel_line;
        
        const char* sub_package_name = sub->op_package->uv.package->op_name->uv.name;
        const char* sub_name = sub->op_name->uv.name;
        const char* file = op_sub->file;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* sub_package_name = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* file = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)file);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , line);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    exception_flag = 0;\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_package_name, sub_name, file, line));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer ,  opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_IF_CROAK_RETURN: {
        SPVM_OP* op_sub = SPVM_LIST_fetch(package->op_subs, opcode->operand1);
        SPVM_SUB* sub = op_sub->uv.sub;
        int32_t sub_id = sub->id;
        int32_t rel_line = opcode->operand2;
        int32_t line = op_sub->line + rel_line;
        
        const char* sub_package_name = sub->op_package->uv.package->op_name->uv.name;
        const char* sub_name = sub->op_name->uv.name;
        const char* file = op_sub->file;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (exception_flag) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* sub_package_name = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)package_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* sub_name = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)sub_name);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    const char* file = \"");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , (char*)file);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "\";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    int32_t line = ");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , line);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    env->set_exception(env, env->create_exception_stack_trace(env, env->get_exception(env), sub_package_name, sub_name, file, line));\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        break;
      }
      case SPVM_OPCODE_C_ID_SET_CROAK_FLAG_TRUE: {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  exception_flag = 1;\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_VOID:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN:
      {
        int32_t var_id = opcode->operand0;
        
        // Value type
        if (sub_return_type_is_value_type) {
          for (int32_t offset = 0; offset < sub_return_type_width; offset++) {
            switch (sub_return_type->basic_type->id) {
              case SPVM_BASIC_TYPE_C_ID_BYTE: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_SHORT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_INT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_LONG: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_FLOAT: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
                SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
                SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
                SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", var_id + offset);
                SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
                break;
              }
              default:
                assert(0);
            }
          }
        }
        // Object type
        else if (sub_return_type_is_object_type) {
          SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
          SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "void*", 0);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
          SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", var_id);
          SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        }
        // Numeric type
        else {
          switch (sub_return_basic_type_id) {
            case SPVM_BASIC_TYPE_C_ID_BYTE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_byte", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_byte", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_SHORT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_short", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_short", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_INT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_int", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_LONG: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_long", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_long", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_FLOAT: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_float", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_float", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            case SPVM_BASIC_TYPE_C_ID_DOUBLE: {
              SPVM_STRING_BUFFER_add(compiler, string_buffer , "  ");
              SPVM_CSOURCE_BUILDER_add_stack(compiler, string_buffer, "SPVM_VALUE_double", 0);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , " = ");
              SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_double", var_id);
              SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
              break;
            }
            default:
              assert(0);
          }
        }
                    
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_OBJECT:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  *(void**)&stack[0] = ");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "void*", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        
        // Increment ref count of return value not to release by decrement
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (*(void**)&stack[0] != NULL) {\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    SPVM_RUNTIME_C_INLINE_INC_REF_COUNT_ONLY(*(void**)&stack[0]);\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_RETURN_UNDEF:
      {
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  *(void**)&stack[0] = NULL;\n");
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode->operand1);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        
        break;
      }
      case SPVM_OPCODE_C_ID_LOOKUP_SWITCH: {
        int32_t rel_id = opcode->operand2;
        SPVM_OP* op_switch_info = SPVM_LIST_fetch(sub->op_switch_infos, rel_id);
        SPVM_SWITCH_INFO* switch_info = op_switch_info->uv.switch_info;
        SPVM_LIST* op_cases = switch_info->op_cases_ordered;

        // default offset
        int32_t default_opcode_rel_index = switch_info->default_opcode_rel_index;
        
        // case count
        int32_t cases_length = op_cases->length;
        
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  switch(");
        SPVM_CSOURCE_BUILDER_add_operand(compiler, string_buffer, "SPVM_VALUE_int", opcode->operand0);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ") {\n");
        {
          int32_t case_index;
          for (case_index = 0; case_index < cases_length; case_index++) {
            SPVM_OP* op_case = SPVM_LIST_fetch(op_cases, case_index);
            int32_t match = op_case->uv.case_info->op_constant->uv.constant->value.ival;
            int32_t opcode_rel_index = op_case->uv.case_info->opcode_rel_index;
            
            SPVM_STRING_BUFFER_add(compiler, string_buffer , "    case ");
            SPVM_STRING_BUFFER_add_int(compiler, string_buffer , match);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ": goto L");
            SPVM_STRING_BUFFER_add_int(compiler, string_buffer , opcode_rel_index);
            SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
          }
        }
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "    default: goto L");
        SPVM_STRING_BUFFER_add_int(compiler, string_buffer , default_opcode_rel_index);
        SPVM_STRING_BUFFER_add(compiler, string_buffer , ";\n");
        SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
      }
    }
    opcode_index++;
  }
  
  // No exception
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  if (!exception_flag) {\n");
  _Bool sub_return_type_is_value_t = SPVM_TYPE_is_value_type(compiler, sub_return_type);
  if (sub_return_type_is_object_type && !sub_return_type_is_value_type) {
    SPVM_STRING_BUFFER_add(compiler, string_buffer , "    if (stack[0].oval != NULL) { SPVM_RUNTIME_C_INLINE_DEC_REF_COUNT_ONLY(stack[0].oval); }\n");
  }
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  }\n");
  
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "  return exception_flag;\n");
  
  // Close subroutine
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "}\n");
  SPVM_STRING_BUFFER_add(compiler, string_buffer , "\n");
}
