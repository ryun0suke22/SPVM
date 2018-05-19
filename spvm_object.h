#ifndef SPVM_OBJECT_H
#define SPVM_OBJECT_H

#include "spvm_base.h"
#include "spvm_api.h"

enum {
  SPVM_OBJECT_C_CATEGORY_OBJECT,
  SPVM_OBJECT_C_CATEGORY_NUMERIC_ARRAY,
  SPVM_OBJECT_C_CATEGORY_OBJECT_ARRAY,
  SPVM_OBJECT_C_CATEGORY_ADDRESS_ARRAY,
  SPVM_OBJECT_C_CATEGORY_CALL_STACK,
};

// SPVM_OBJECT
struct SPVM_object {
  SPVM_OBJECT* weaken_back_refs;
  int32_t ref_count;
  int32_t weaken_back_refs_length;
  int32_t units_length;
  int32_t basic_type_id;
  int8_t unit_byte_size;
  int8_t has_destructor;
  int8_t in_destroy;
  int8_t category;
  uint8_t dimension;
};

#endif
