#include "spvm_opcode.h"
#include "spvm_compiler.h"
#include "spvm_compiler_allocator.h"





























































































const char* const* SPVM_OPCODE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "END_METHOD",
    "MULNUM_ARRAY_FIELD_FETCH_BYTE",
    "MULNUM_ARRAY_FIELD_FETCH_SHORT",
    "MULNUM_ARRAY_FIELD_FETCH_INT",
    "MULNUM_ARRAY_FIELD_FETCH_LONG",
    "MULNUM_ARRAY_FIELD_FETCH_FLOAT",
    "MULNUM_ARRAY_FIELD_FETCH_DOUBLE",
    "MULNUM_ARRAY_FIELD_STORE_BYTE",
    "MULNUM_ARRAY_FIELD_STORE_SHORT",
    "MULNUM_ARRAY_FIELD_STORE_INT",
    "MULNUM_ARRAY_FIELD_STORE_LONG",
    "MULNUM_ARRAY_FIELD_STORE_FLOAT",
    "MULNUM_ARRAY_FIELD_STORE_DOUBLE",
    "MULNUM_ARRAY_FETCH_BYTE",
    "MULNUM_ARRAY_FETCH_SHORT",
    "MULNUM_ARRAY_FETCH_INT",
    "MULNUM_ARRAY_FETCH_LONG",
    "MULNUM_ARRAY_FETCH_FLOAT",
    "MULNUM_ARRAY_FETCH_DOUBLE",
    "MULNUM_ARRAY_STORE_BYTE",
    "MULNUM_ARRAY_STORE_SHORT",
    "MULNUM_ARRAY_STORE_INT",
    "MULNUM_ARRAY_STORE_LONG",
    "MULNUM_ARRAY_STORE_FLOAT",
    "MULNUM_ARRAY_STORE_DOUBLE",
    "MULNUM_DEREF_BYTE",
    "MULNUM_DEREF_SHORT",
    "MULNUM_DEREF_INT",
    "MULNUM_DEREF_LONG",
    "MULNUM_DEREF_FLOAT",
    "MULNUM_DEREF_DOUBLE",
    "MULNUM_DEREF_GET_FIELD_BYTE",
    "MULNUM_DEREF_GET_FETCH_SHORT",
    "MULNUM_DEREF_GET_FETCH_INT",
    "MULNUM_DEREF_GET_FETCH_LONG",
    "MULNUM_DEREF_GET_FETCH_FLOAT",
    "MULNUM_DEREF_GET_FETCH_DOUBLE",
    "MULNUM_DEREF_SET_FIELD_BYTE",
    "MULNUM_DEREF_SET_FIELD_SHORT",
    "MULNUM_DEREF_SET_FIELD_INT",
    "MULNUM_DEREF_SET_FIELD_LONG",
    "MULNUM_DEREF_SET_FIELD_FLOAT",
    "MULNUM_DEREF_SET_FIELD_DOUBLE",
    "MULNUM_MOVE_BYTE",
    "MULNUM_MOVE_SHORT",
    "MULNUM_MOVE_INT",
    "MULNUM_MOVE_LONG",
    "MULNUM_MOVE_FLOAT",
    "MULNUM_MOVE_DOUBLE",
    "MULNUM_SET_FIELD_BYTE",
    "MULNUM_SET_FIELD_SHORT",
    "MULNUM_SET_FIELD_INT",
    "MULNUM_SET_FIELD_LONG",
    "MULNUM_SET_FIELD_FLOAT",
    "MULNUM_SET_FIELD_DOUBLE",
    "MULNUM_GET_FIELD_BYTE",
    "MULNUM_GET_FIELD_SHORT",
    "MULNUM_GET_FIELD_INT",
    "MULNUM_GET_FIELD_LONG",
    "MULNUM_GET_FIELD_FLOAT",
    "MULNUM_GET_FIELD_DOUBLE",
    "CALL_METHOD_VOID",
    "CALL_METHOD_BYTE",
    "CALL_METHOD_SHORT",
    "CALL_METHOD_INT",
    "CALL_METHOD_LONG",
    "CALL_METHOD_FLOAT",
    "CALL_METHOD_DOUBLE",
    "CALL_METHOD_OBJECT",
    "CALL_METHOD_MULNUM_BYTE",
    "CALL_METHOD_MULNUM_SHORT",
    "CALL_METHOD_MULNUM_INT",
    "CALL_METHOD_MULNUM_LONG",
    "CALL_METHOD_MULNUM_FLOAT",
    "CALL_METHOD_MULNUM_DOUBLE",
    "CALL_CALLBACK_METHOD_VOID",
    "CALL_CALLBACK_METHOD_BYTE",
    "CALL_CALLBACK_METHOD_SHORT",
    "CALL_CALLBACK_METHOD_INT",
    "CALL_CALLBACK_METHOD_LONG",
    "CALL_CALLBACK_METHOD_FLOAT",
    "CALL_CALLBACK_METHOD_DOUBLE",
    "CALL_CALLBACK_METHOD_OBJECT",
    "CALL_CALLBACK_METHOD_MULNUM_BYTE",
    "CALL_CALLBACK_METHOD_MULNUM_SHORT",
    "CALL_CALLBACK_METHOD_MULNUM_INT",
    "CALL_CALLBACK_METHOD_MULNUM_LONG",
    "CALL_CALLBACK_METHOD_MULNUM_FLOAT",
    "CALL_CALLBACK_METHOD_MULNUM_DOUBLE",
    "ADD_INT",
    "ADD_LONG",
    "ADD_FLOAT",
    "ADD_DOUBLE",
    "METHODTRACT_INT",
    "METHODTRACT_LONG",
    "METHODTRACT_FLOAT",
    "METHODTRACT_DOUBLE",
    "MULTIPLY_INT",
    "MULTIPLY_LONG",
    "MULTIPLY_FLOAT",
    "MULTIPLY_DOUBLE",
    "DIVIDE_INT",
    "DIVIDE_LONG",
    "DIVIDE_FLOAT",
    "DIVIDE_DOUBLE",
    "REMAINDER_INT",
    "REMAINDER_LONG",
    "LEFT_SHIFT_INT",
    "LEFT_SHIFT_LONG",
    "RIGHT_ARITHMETIC_SHIFT_INT",
    "RIGHT_ARITHMETIC_SHIFT_LONG",
    "RIGHT_LOGICAL_SHIFT_INT",
    "RIGHT_LOGICAL_SHIFT_LONG",
    "BIT_AND_INT",
    "BIT_AND_LONG",
    "BIT_OR_INT",
    "BIT_OR_LONG",
    "BIT_XOR_INT",
    "BIT_XOR_LONG",
    "BIT_OMPLEMENT_INT",
    "BIT_NOT_LONG",
    "NEGATE_INT",
    "NEGATE_LONG",
    "NEGATE_FLOAT",
    "NEGATE_DOUBLE",
    "INIT_BYTE",
    "INIT_SHORT",
    "INIT_INT",
    "INIT_LONG",
    "INIT_FLOAT",
    "INIT_DOUBLE",
    "INIT_UNDEF",
    "INIT_MULNUM_BYTE",
    "INIT_MULNUM_SHORT",
    "INIT_MULNUM_INT",
    "INIT_MULNUM_LONG",
    "INIT_MULNUM_FLOAT",
    "INIT_MULNUM_DOUBLE",
    "MOVE_CONSTANT_BYTE",
    "MOVE_CONSTANT_INT",
    "MOVE_CONSTANT_LONG",
    "MOVE_CONSTANT_FLOAT",
    "MOVE_CONSTANT_DOUBLE",
    "MOVE_BYTE",
    "MOVE_SHORT",
    "MOVE_INT",
    "MOVE_LONG",
    "MOVE_FLOAT",
    "MOVE_DOUBLE",
    "MOVE_OBJECT",
    "MOVE_UNDEF",
    "MOVE_REF",
    "CONVERT_BYTE_TO_SHORT",
    "CONVERT_BYTE_TO_INT",
    "CONVERT_BYTE_TO_LONG",
    "CONVERT_BYTE_TO_FLOAT",
    "CONVERT_BYTE_TO_DOUBLE",
    "CONVERT_SHORT_TO_BYTE",
    "CONVERT_SHORT_TO_INT",
    "CONVERT_SHORT_TO_LONG",
    "CONVERT_SHORT_TO_FLOAT",
    "CONVERT_SHORT_TO_DOUBLE",
    "CONVERT_INT_TO_BYTE",
    "CONVERT_INT_TO_SHORT",
    "CONVERT_INT_TO_LONG",
    "CONVERT_INT_TO_FLOAT",
    "CONVERT_INT_TO_DOUBLE",
    "CONVERT_LONG_TO_BYTE",
    "CONVERT_LONG_TO_SHORT",
    "CONVERT_LONG_TO_INT",
    "CONVERT_LONG_TO_FLOAT",
    "CONVERT_LONG_TO_DOUBLE",
    "CONVERT_FLOAT_TO_BYTE",
    "CONVERT_FLOAT_TO_SHORT",
    "CONVERT_FLOAT_TO_INT",
    "CONVERT_FLOAT_TO_LONG",
    "CONVERT_FLOAT_TO_DOUBLE",
    "CONVERT_DOUBLE_TO_BYTE",
    "CONVERT_DOUBLE_TO_SHORT",
    "CONVERT_DOUBLE_TO_INT",
    "CONVERT_DOUBLE_TO_LONG",
    "CONVERT_DOUBLE_TO_FLOAT",
    "CONVERT_BYTE_TO_STRING",
    "CONVERT_SHORT_TO_STRING",
    "CONVERT_INT_TO_STRING",
    "CONVERT_LONG_TO_STRING",
    "CONVERT_FLOAT_TO_STRING",
    "CONVERT_DOUBLE_TO_STRING",
    "CONVERT_STRING_TO_BYTE_ARRAY",
    "CONVERT_BYTE_ARRAY_TO_STRING",
    "CONVERT_BYTE_TO_BYTE_OBJECT",
    "CONVERT_SHORT_TO_SHORT_OBJECT",
    "CONVERT_INT_TO_INT_OBJECT",
    "CONVERT_LONG_TO_LONG_OBJECT",
    "CONVERT_FLOAT_TO_FLOAT_OBJECT",
    "CONVERT_DOUBLE_TO_DOUBLE_OBJECT",
    "CONVERT_BYTE_OBJECT_TO_BYTE",
    "CONVERT_SHORT_OBJECT_TO_SHORT",
    "CONVERT_INT_OBJECT_TO_INT",
    "CONVERT_LONG_OBJECT_TO_LONG",
    "CONVERT_FLOAT_OBJECT_TO_FLOAT",
    "CONVERT_DOUBLE_OBJECT_TO_DOUBLE",
    "CONCAT",
    "EQ_INT",
    "EQ_LONG",
    "EQ_FLOAT",
    "EQ_DOUBLE",
    "EQ_OBJECT",
    "NE_INT",
    "NE_LONG",
    "NE_FLOAT",
    "NE_DOUBLE",
    "NE_OBJECT",
    "GT_INT",
    "GT_LONG",
    "GT_FLOAT",
    "GT_DOUBLE",
    "GE_INT",
    "GE_LONG",
    "GE_FLOAT",
    "GE_DOUBLE",
    "LT_INT",
    "LT_LONG",
    "LT_FLOAT",
    "LT_DOUBLE",
    "LE_INT",
    "LE_LONG",
    "LE_FLOAT",
    "LE_DOUBLE",
    "CMP_INT",
    "CMP_LONG",
    "CMP_FLOAT",
    "CMP_DOUBLE",
    "IS_UNDEF",
    "IS_NOT_UNDEF",
    "STRING_EQ",
    "STRING_NE",
    "STRING_GT",
    "STRING_GE",
    "STRING_LT",
    "STRING_LE",
    "STRING_CMP",
    "BOOL_INT",
    "BOOL_LONG",
    "BOOL_FLOAT",
    "BOOL_DOUBLE",
    "BOOL_OBJECT",
    "GOTO",
    "IF_EQ_ZERO",
    "IF_NE_ZERO",
    "IF_EXCEPTION_CATCH",
    "IF_EXCEPTION_RETURN",
    "LOOKUP_SWITCH",
    "ARRAY_FETCH_BYTE",
    "ARRAY_FETCH_SHORT",
    "ARRAY_FETCH_INT",
    "ARRAY_FETCH_LONG",
    "ARRAY_FETCH_FLOAT",
    "ARRAY_FETCH_DOUBLE",
    "ARRAY_FETCH_OBJECT",
    "ARRAY_STORE_BYTE",
    "ARRAY_STORE_SHORT",
    "ARRAY_STORE_INT",
    "ARRAY_STORE_LONG",
    "ARRAY_STORE_FLOAT",
    "ARRAY_STORE_DOUBLE",
    "ARRAY_STORE_OBJECT",
    "ARRAY_STORE_OBJECT_CHECK_TYPE",
    "ARRAY_STORE_UNDEF",
    "ARRAY_LENGTH",
    "NEW_OBJECT",
    "NEW_STRING",
    "NEW_OBJECT_ARRAY",
    "NEW_MULTI_ARRAY",
    "NEW_MULNUM_ARRAY",
    "NEW_BYTE_ARRAY",
    "NEW_SHORT_ARRAY",
    "NEW_INT_ARRAY",
    "NEW_LONG_ARRAY",
    "NEW_FLOAT_ARRAY",
    "NEW_DOUBLE_ARRAY",
    "GET_FIELD_BYTE",
    "GET_FIELD_SHORT",
    "GET_FIELD_INT",
    "GET_FIELD_LONG",
    "GET_FIELD_FLOAT",
    "GET_FIELD_DOUBLE",
    "GET_FIELD_OBJECT",
    "SET_FIELD_BYTE",
    "SET_FIELD_SHORT",
    "SET_FIELD_INT",
    "SET_FIELD_LONG",
    "SET_FIELD_FLOAT",
    "SET_FIELD_DOUBLE",
    "SET_FIELD_OBJECT",
    "SET_FIELD_UNDEF",
    "IS_TYPE",
    "HAS_CALLBACK",
    "CHECK_OBJECT_TYPE",
    "CHECK_CALLBACK",
    "ENTER_SCOPE",
    "PUSH_MORTAL",
    "LEAVE_SCOPE",
    "PUSH_ARG_BYTE",
    "PUSH_ARG_SHORT",
    "PUSH_ARG_INT",
    "PUSH_ARG_LONG",
    "PUSH_ARG_FLOAT",
    "PUSH_ARG_DOUBLE",
    "PUSH_ARG_OBJECT",
    "PUSH_ARG_REF",
    "PUSH_ARG_UNDEF",
    "PUSH_ARG_MULNUM_BYTE",
    "PUSH_ARG_MULNUM_SHORT",
    "PUSH_ARG_MULNUM_INT",
    "PUSH_ARG_MULNUM_LONG",
    "PUSH_ARG_MULNUM_FLOAT",
    "PUSH_ARG_MULNUM_DOUBLE",
    "RETURN_VOID",
    "RETURN_BYTE",
    "RETURN_SHORT",
    "RETURN_INT",
    "RETURN_LONG",
    "RETURN_FLOAT",
    "RETURN_DOUBLE",
    "RETURN_OBJECT",
    "RETURN_UNDEF",
    "RETURN_MULNUM_BYTE",
    "RETURN_MULNUM_SHORT",
    "RETURN_MULNUM_INT",
    "RETURN_MULNUM_LONG",
    "RETURN_MULNUM_FLOAT",
    "RETURN_MULNUM_DOUBLE",
    "SET_CROAK_FLAG_TRUE",
    "DIE",
    "WARN",
    "PRINT",
    "REF",
    "REF_BYTE",
    "REF_SHORT",
    "REF_INT",
    "REF_LONG",
    "REF_FLOAT",
    "REF_DOUBLE",
    "GET_DEREF_BYTE",
    "GET_DEREF_SHORT",
    "GET_DEREF_INT",
    "GET_DEREF_LONG",
    "GET_DEREF_FLOAT",
    "GET_DEREF_DOUBLE",
    "SET_DEREF_BYTE",
    "SET_DEREF_SHORT",
    "SET_DEREF_INT",
    "SET_DEREF_LONG",
    "SET_DEREF_FLOAT",
    "SET_DEREF_DOUBLE",
    "GET_PACKAGE_VAR_BYTE",
    "GET_PACKAGE_VAR_SHORT",
    "GET_PACKAGE_VAR_INT",
    "GET_PACKAGE_VAR_LONG",
    "GET_PACKAGE_VAR_FLOAT",
    "GET_PACKAGE_VAR_DOUBLE",
    "GET_PACKAGE_VAR_OBJECT",
    "SET_PACKAGE_VAR_BYTE",
    "SET_PACKAGE_VAR_SHORT",
    "SET_PACKAGE_VAR_INT",
    "SET_PACKAGE_VAR_LONG",
    "SET_PACKAGE_VAR_FLOAT",
    "SET_PACKAGE_VAR_DOUBLE",
    "SET_PACKAGE_VAR_OBJECT",
    "SET_PACKAGE_VAR_UNDEF",
    "GET_EXCEPTION_VAR",
    "SET_EXCEPTION_VAR",
    "SET_EXCEPTION_UNDEF",
    "WEAKEN_FIELD",
    "UNWEAKEN_FIELD",
    "ISWEAK_FIELD",
    "REFCNT",
    "REFOP",
    "DUMP",
  };
  
  return id_names;
}

SPVM_OPCODE* SPVM_OPCODE_new(SPVM_COMPILER* compiler) {
  SPVM_OPCODE* opcode = SPVM_COMPILER_ALLOCATOR_safe_malloc_zero(compiler, sizeof(SPVM_OPCODE));
  
  return opcode;
}
