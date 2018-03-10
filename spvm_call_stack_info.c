#include "spvm_call_stack_info.h"
#include "spvm_runtime.h"
#include "spvm_constant_pool_sub.h"

#include "spvm_package.h"
#include "spvm_sub.h"
#include "spvm_package.h"
#include "spvm_type.h"
#include "spvm_field.h"
#include "spvm_compiler.h"
#include "spvm_my.h"
#include "spvm_op.h"
#include "spvm_list.h"
#include "spvm_constant_pool.h"

void SPVM_CALL_STACK_init_call_stack_info(SPVM_CALL_STACK_INFO* call_stack_info, SPVM_RUNTIME* runtime, int32_t sub_id) {
  SPVM_COMPILER* compiler = runtime->compiler;
  int32_t* constant_pool = compiler->constant_pool->values;

  SPVM_CONSTANT_POOL_SUB* constant_pool_sub = (SPVM_CONSTANT_POOL_SUB*)&constant_pool[sub_id];
  int32_t op_sub_id = constant_pool_sub->op_sub_id;
  SPVM_OP* op_sub = SPVM_LIST_fetch(compiler->op_subs, op_sub_id);
  SPVM_SUB* sub = op_sub->uv.sub;
  
  // Length
  call_stack_info->length = sub->op_mys->length + 1 + sub->auto_dec_ref_count_stack_max_length;
  
  call_stack_info->auto_dec_ref_count_stack_top_index = sub->op_mys->length;
  call_stack_info->auto_dec_ref_count_stack_base = call_stack_info->auto_dec_ref_count_stack_top_index + 1;
}
