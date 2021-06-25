#ifndef SPVM_PACKAGE_H
#define SPVM_PACKAGE_H

#include "spvm_typedecl.h"

enum {
  SPVM_PACKAGE_C_CATEGORY_CLASS,
  SPVM_PACKAGE_C_CATEGORY_CALLBACK,
  SPVM_PACKAGE_C_CATEGORY_VALUE,
};

enum {
  SPVM_PACKAGE_C_FLAG_POINTER = 1,
  SPVM_PACKAGE_C_FLAG_ANON_METHOD_PACKAGE = 2,
  SPVM_PACKAGE_C_FLAG_PUBLIC = 4,
};

struct spvm_package {
  SPVM_OP* op_package;
  SPVM_OP* op_name;
  SPVM_LIST* package_vars;
  SPVM_HASH* package_var_symtable;
  SPVM_LIST* methods;
  SPVM_HASH* method_symtable;
  SPVM_LIST* fields;
  SPVM_HASH* field_symtable;
  SPVM_METHOD* method_destructor;
  SPVM_LIST* info_package_var_ids;
  SPVM_HASH* info_package_var_id_symtable;
  SPVM_LIST* info_method_ids;
  SPVM_HASH* info_method_id_symtable;
  SPVM_LIST* info_field_ids;
  SPVM_HASH* info_field_id_symtable;
  SPVM_LIST* info_basic_type_ids;
  SPVM_HASH* info_basic_type_id_symtable;
  SPVM_LIST* info_switch_infos;
  SPVM_LIST* info_constants;
  const char* module_file;
  const char* module_rel_file;
  SPVM_OP* op_type;
  SPVM_LIST* op_uses;
  SPVM_LIST* op_allows;
  int32_t id;
  int32_t fields_byte_size;
  int32_t object_fields_offset;
  int32_t object_fields_length;
  int32_t flag;
  int32_t category;
  const char* name;
  SPVM_OP* op_begin_method;
  int32_t fail_load;
  int32_t has_precompile_descriptor;
  SPVM_LIST* anon_methods;
  int8_t is_anon;
};

SPVM_PACKAGE* SPVM_PACKAGE_new(SPVM_COMPILER* compiler);
const char* const* SPVM_PACKAGE_C_CATEGORY_NAMES(void);

#endif
