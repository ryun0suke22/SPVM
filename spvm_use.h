#ifndef SPVM_USE_H
#define SPVM_USE_H

#include "spvm_base.h"

struct SPVM_use {
  SPVM_OP* op_name;
  SPVM_DYNAMIC_ARRAY* template_args;
};

#endif
