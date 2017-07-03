#ifndef SPVM_RUNTIME_API_H
#define SPVM_RUNTIME_API_H

#include "spvm_base.h"
#include "spvm_env.h"

int64_t SPVM_RUNTIME_API_calcurate_data_byte_size(SPVM_ENV* env, SPVM_DATA* data);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte(SPVM_ENV* env, int32_t length);
SPVM_DATA_ARRAY* SPVM_RUNTIME_API_create_data_array_byte_from_pv(SPVM_ENV* env, const char* pv);
void SPVM_RUNTIME_API_dec_ref_count(SPVM_ENV* env, SPVM_DATA* data);
void SPVM_RUNTIME_API_inc_ref_count(SPVM_ENV* env, SPVM_DATA* data);
void SPVM_RUNTIME_API_push_return_value_byte(SPVM_ENV* env, int8_t value);
void SPVM_RUNTIME_API_push_return_value_short(SPVM_ENV* env, int16_t value);
void SPVM_RUNTIME_API_push_return_value_int(SPVM_ENV* env, int32_t value);
void SPVM_RUNTIME_API_push_return_value_long(SPVM_ENV* env, int64_t value);
void SPVM_RUNTIME_API_push_return_value_float(SPVM_ENV* env, float value);
void SPVM_RUNTIME_API_push_return_value_double(SPVM_ENV* env, double value);
void SPVM_RUNTIME_API_push_ret(SPVM_ENV* env, void* value);
int8_t SPVM_RUNTIME_API_pop_return_value_byte(SPVM_ENV* env);
int16_t SPVM_RUNTIME_API_pop_return_value_short(SPVM_ENV* env);
int32_t SPVM_RUNTIME_API_pop_return_value_int(SPVM_ENV* env);
int64_t SPVM_RUNTIME_API_pop_return_value_long(SPVM_ENV* env);
float SPVM_RUNTIME_API_pop_return_value_float(SPVM_ENV* env);
double SPVM_RUNTIME_API_pop_return_value_double(SPVM_ENV* env);
void* SPVM_RUNTIME_API_pop_return_value_address(SPVM_ENV* env);
int8_t SPVM_RUNTIME_API_get_var_byte(SPVM_ENV* env, int32_t index);
int16_t SPVM_RUNTIME_API_get_var_short(SPVM_ENV* env, int32_t index);
int32_t SPVM_RUNTIME_API_get_var_int(SPVM_ENV* env, int32_t index);
int64_t SPVM_RUNTIME_API_get_var_long(SPVM_ENV* env, int32_t index);
float SPVM_RUNTIME_API_get_var_float(SPVM_ENV* env, int32_t index);
double SPVM_RUNTIME_API_get_var_double(SPVM_ENV* env, int32_t index);
void* SPVM_RUNTIME_API_get_var_address(SPVM_ENV* env, int32_t index);
void SPVM_RUNTIME_API_push_var_byte(SPVM_ENV* env, int8_t value);
void SPVM_RUNTIME_API_push_var_short(SPVM_ENV* env, int16_t value);
void SPVM_RUNTIME_API_push_var_int(SPVM_ENV* env, int32_t value);
void SPVM_RUNTIME_API_push_var_long(SPVM_ENV* env, int64_t value);
void SPVM_RUNTIME_API_push_var_float(SPVM_ENV* env, float value);
void SPVM_RUNTIME_API_push_var_double(SPVM_ENV* env, double value);
void SPVM_RUNTIME_API_push_var_address(SPVM_ENV* env, void* value);


int32_t SPVM_RUNTIME_API_get_array_value_size(SPVM_ENV* env, int32_t type);
SPVM_VALUE* SPVM_RUNTIME_API_get_object_fields(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
int32_t SPVM_RUNTIME_API_get_object_field_index(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, const char* name);
int32_t SPVM_RUNTIME_API_get_object_fields_length(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
void SPVM_RUNTIME_API_set_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, int8_t value);
void SPVM_RUNTIME_API_set_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, int16_t value);
void SPVM_RUNTIME_API_set_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, int32_t value);
void SPVM_RUNTIME_API_set_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, int64_t value);
void SPVM_RUNTIME_API_set_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, float value);
void SPVM_RUNTIME_API_set_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index, double value);
int8_t SPVM_RUNTIME_API_get_object_field_value_byte(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int16_t SPVM_RUNTIME_API_get_object_field_value_short(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int32_t SPVM_RUNTIME_API_get_object_field_value_int(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int64_t SPVM_RUNTIME_API_get_object_field_value_long(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
float SPVM_RUNTIME_API_get_object_field_value_float(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
double SPVM_RUNTIME_API_get_object_field_value_double(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
SPVM_DATA* SPVM_RUNTIME_API_get_object_field_value_ref(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object, int32_t field_index);
int32_t SPVM_RUNTIME_API_dump_object_field_names(SPVM_ENV* env, SPVM_DATA_OBJECT* data_object);
int32_t SPVM_RUNTIME_API_get_ref_count(SPVM_ENV* env, SPVM_DATA* data);
int32_t SPVM_RUNTIME_API_get_array_length(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int8_t* SPVM_RUNTIME_API_get_array_values_byte(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int16_t* SPVM_RUNTIME_API_get_array_values_short(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int32_t* SPVM_RUNTIME_API_get_array_values_int(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
int64_t* SPVM_RUNTIME_API_get_array_values_long(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
float* SPVM_RUNTIME_API_get_array_values_float(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
double* SPVM_RUNTIME_API_get_array_values_double(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);
SPVM_DATA** SPVM_RUNTIME_API_get_array_values_ref(SPVM_ENV* env, SPVM_DATA_ARRAY* data_array);

#endif
