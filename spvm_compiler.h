#ifndef SPVM_COMPILER_H
#define SPVM_COMPILER_H

#include <stdio.h>

#include "spvm_base.h"

// Parser information
struct SPVM_compiler {
  // Constant pool
  SPVM_CONSTANT_POOL* constant_pool;
  
  // String symbol table
  SPVM_HASH* string_symtable;
  
  // Opcodes
  SPVM_OPCODE_ARRAY* opcode_array;

  // Entry point package name
  const char* entry_point_package_name;
  
  // Entry point subroutine name
  const char* entry_point_sub_name;

  // Allocator
  SPVM_COMPILER_ALLOCATOR* allocator;
  
  // Before buffer position
  char* befbufptr;
  
  // Current buffer position
  char* bufptr;
  
  // Current file name
  const char* cur_file;
  
  const char* cur_package_name_with_template_args;
  
  // Source base_object
  char* cur_src;
  
  // AST grammar
  SPVM_OP* op_grammar;
  
  // Constants
  SPVM_LIST* op_constants;
  
  int64_t enum_default_value;
  int32_t enum_default_type_code;

  // Packages
  SPVM_LIST* op_packages;
  
  // OP package symtable
  SPVM_HASH* op_package_symtable;
  
  // OP our symtable
  SPVM_HASH* op_our_symtable;
  
  // Class loading stack
  SPVM_LIST* op_use_stack;
  
  // Include pathes
  SPVM_LIST* include_pathes;
  
  // Subroutine ops
  SPVM_LIST* op_subs;
  
  // Subroutine absolute name symbol table
  SPVM_HASH* op_sub_symtable;

  // use symbol table
  SPVM_HASH* op_use_symtable;
  
  // Types(This is all type ops in source code)
  SPVM_LIST* op_types;
  
  // Types(This is unique types)
  SPVM_LIST* types;
  
  // Resolved type symbol table
  SPVM_HASH* type_symtable;
  
  // Current case statements in switch statement
  SPVM_LIST* cur_op_cases;
  
  // Entry point subroutine name
  const char* start_sub_name;
  
  SPVM_LIST* cur_template_args;

  // Use module pathes
  SPVM_HASH* package_load_path_symtable;
  
  // Current line number
  int32_t cur_line;
  
  // Syntax error count
  int32_t error_count;
  
  // Current package count
  int32_t current_package_count;
  
  // Package indexes constant pool index
  int32_t packages_base;

  // Type indexes constant pool index
  int32_t types_base;

  // Type code to id index
  int32_t type_code_to_id_base;
  
  // Package Variable id
  int32_t package_var_length;
  
  int32_t tmp_var_index;
  
  // Error is fatal
  _Bool fatal_error;
  
  // Before is camma
  _Bool before_is_comma;
  
  // Before is package
  _Bool before_is_package;
  
  // Expect name
  _Bool expect_name;
  
  SPVM_OP* cur_op_use;
};

SPVM_COMPILER* SPVM_COMPILER_new();
int32_t SPVM_COMPILER_compile(SPVM_COMPILER* compiler);
SPVM_RUNTIME* SPVM_COMPILER_new_runtime(SPVM_COMPILER* compiler);
void SPVM_COMPILER_free(SPVM_COMPILER* compiler);

#endif
