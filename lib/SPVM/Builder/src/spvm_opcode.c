#include "spvm_opcode.h"
#include "spvm_compiler.h"
#include "spvm_allocator.h"





























































































const char* const* SPVM_OPCODE_C_ID_NAMES(void) {

  static const char* const id_names[] = {
    "END_METHOD",
    "ADD_INT",
    "ADD_LONG",
    "ADD_FLOAT",
    "ADD_DOUBLE",
    "SUBTRACT_INT",
    "SUBTRACT_LONG",
    "SUBTRACT_FLOAT",
    "SUBTRACT_DOUBLE",
    "MULTIPLY_INT",
    "MULTIPLY_LONG",
    "MULTIPLY_FLOAT",
    "MULTIPLY_DOUBLE",
    "DIVIDE_INT",
    "DIVIDE_LONG",
    "DIVIDE_FLOAT",
    "DIVIDE_DOUBLE",
    "DIVIDE_UNSIGNED_INT",
    "DIVIDE_UNSIGNED_LONG",
    "REMAINDER_INT",
    "REMAINDER_LONG",
    "REMAINDER_UNSIGNED_INT",
    "REMAINDER_UNSIGNED_LONG",
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
    "MOVE_OBJECT_CHECK_ASSIGN",
    "MOVE_OBJECT_CHECK_READ_ONLY",
    "MOVE_UNDEF",
    "MOVE_REF",
    "TYPE_CONVERSION_BYTE_TO_SHORT",
    "TYPE_CONVERSION_BYTE_TO_INT",
    "TYPE_CONVERSION_BYTE_TO_LONG",
    "TYPE_CONVERSION_BYTE_TO_FLOAT",
    "TYPE_CONVERSION_BYTE_TO_DOUBLE",
    "TYPE_CONVERSION_SHORT_TO_BYTE",
    "TYPE_CONVERSION_SHORT_TO_INT",
    "TYPE_CONVERSION_SHORT_TO_LONG",
    "TYPE_CONVERSION_SHORT_TO_FLOAT",
    "TYPE_CONVERSION_SHORT_TO_DOUBLE",
    "TYPE_CONVERSION_INT_TO_BYTE",
    "TYPE_CONVERSION_INT_TO_SHORT",
    "TYPE_CONVERSION_INT_TO_LONG",
    "TYPE_CONVERSION_INT_TO_FLOAT",
    "TYPE_CONVERSION_INT_TO_DOUBLE",
    "TYPE_CONVERSION_LONG_TO_BYTE",
    "TYPE_CONVERSION_LONG_TO_SHORT",
    "TYPE_CONVERSION_LONG_TO_INT",
    "TYPE_CONVERSION_LONG_TO_FLOAT",
    "TYPE_CONVERSION_LONG_TO_DOUBLE",
    "TYPE_CONVERSION_FLOAT_TO_BYTE",
    "TYPE_CONVERSION_FLOAT_TO_SHORT",
    "TYPE_CONVERSION_FLOAT_TO_INT",
    "TYPE_CONVERSION_FLOAT_TO_LONG",
    "TYPE_CONVERSION_FLOAT_TO_DOUBLE",
    "TYPE_CONVERSION_DOUBLE_TO_BYTE",
    "TYPE_CONVERSION_DOUBLE_TO_SHORT",
    "TYPE_CONVERSION_DOUBLE_TO_INT",
    "TYPE_CONVERSION_DOUBLE_TO_LONG",
    "TYPE_CONVERSION_DOUBLE_TO_FLOAT",
    "TYPE_CONVERSION_BYTE_TO_STRING",
    "TYPE_CONVERSION_SHORT_TO_STRING",
    "TYPE_CONVERSION_INT_TO_STRING",
    "TYPE_CONVERSION_LONG_TO_STRING",
    "TYPE_CONVERSION_FLOAT_TO_STRING",
    "TYPE_CONVERSION_DOUBLE_TO_STRING",
    "TYPE_CONVERSION_STRING_TO_BYTE_ARRAY",
    "TYPE_CONVERSION_BYTE_ARRAY_TO_STRING",
    "TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT",
    "TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT",
    "TYPE_CONVERSION_INT_TO_INT_OBJECT",
    "TYPE_CONVERSION_LONG_TO_LONG_OBJECT",
    "TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT",
    "TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT",
    "TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE",
    "TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT",
    "TYPE_CONVERSION_INT_OBJECT_TO_INT",
    "TYPE_CONVERSION_LONG_OBJECT_TO_LONG",
    "TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT",
    "TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE",
    "TYPE_CONVERSION_CONDITINAL_INT",
    "TYPE_CONVERSION_CONDITINAL_LONG",
    "TYPE_CONVERSION_CONDITINAL_FLOAT",
    "TYPE_CONVERSION_CONDITINAL_DOUBLE",
    "TYPE_CONVERSION_CONDITINAL_OBJECT",
    "TYPE_CONVERSION_CONDITINAL_BOOL_OBJECT",
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
    "GOTO",
    "IF_EQ_ZERO",
    "IF_NE_ZERO",
    "IF_EXCEPTION_CATCH",
    "IF_EXCEPTION_RETURN",
    "LOOKUP_SWITCH",
    "CASE_INFO",
    "GET_ARRAY_ELEMENT_BYTE",
    "GET_ARRAY_ELEMENT_SHORT",
    "GET_ARRAY_ELEMENT_INT",
    "GET_ARRAY_ELEMENT_LONG",
    "GET_ARRAY_ELEMENT_FLOAT",
    "GET_ARRAY_ELEMENT_DOUBLE",
    "GET_ARRAY_ELEMENT_OBJECT",
    "SET_ARRAY_ELEMENT_BYTE",
    "SET_ARRAY_ELEMENT_SHORT",
    "SET_ARRAY_ELEMENT_INT",
    "SET_ARRAY_ELEMENT_LONG",
    "SET_ARRAY_ELEMENT_FLOAT",
    "SET_ARRAY_ELEMENT_DOUBLE",
    "SET_ARRAY_ELEMENT_OBJECT",
    "SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE",
    "SET_ARRAY_ELEMENT_UNDEF",
    "ARRAY_LENGTH",
    "NEW_OBJECT",
    "NEW_OBJECT_ARRAY",
    "NEW_MULTI_ARRAY",
    "NEW_MULNUM_ARRAY",
    "NEW_BYTE_ARRAY",
    "NEW_SHORT_ARRAY",
    "NEW_INT_ARRAY",
    "NEW_LONG_ARRAY",
    "NEW_FLOAT_ARRAY",
    "NEW_DOUBLE_ARRAY",
    "NEW_STRING",
    "NEW_STRING_LEN",
    "IS_READ_ONLY",
    "MAKE_READ_ONLY",
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
    "ISA",
    "HAS_IMPL",
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
    "CALL_CLASS_METHOD_BY_ID",
    "CALL_INSTANCE_METHOD_BY_ID",
    "CALL_INSTANCE_METHOD_BY_SIGNATURE",
    "GET_ARG_BYTE",
    "GET_ARG_SHORT",
    "GET_ARG_INT",
    "GET_ARG_LONG",
    "GET_ARG_FLOAT",
    "GET_ARG_DOUBLE",
    "GET_ARG_OBJECT",
    "GET_ARG_REF",
    "GET_ARG_MULNUM_BYTE",
    "GET_ARG_MULNUM_SHORT",
    "GET_ARG_MULNUM_INT",
    "GET_ARG_MULNUM_LONG",
    "GET_ARG_MULNUM_FLOAT",
    "GET_ARG_MULNUM_DOUBLE",
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
    "GET_CLASS_VAR_BYTE",
    "GET_CLASS_VAR_SHORT",
    "GET_CLASS_VAR_INT",
    "GET_CLASS_VAR_LONG",
    "GET_CLASS_VAR_FLOAT",
    "GET_CLASS_VAR_DOUBLE",
    "GET_CLASS_VAR_OBJECT",
    "SET_CLASS_VAR_BYTE",
    "SET_CLASS_VAR_SHORT",
    "SET_CLASS_VAR_INT",
    "SET_CLASS_VAR_LONG",
    "SET_CLASS_VAR_FLOAT",
    "SET_CLASS_VAR_DOUBLE",
    "SET_CLASS_VAR_OBJECT",
    "SET_CLASS_VAR_UNDEF",
    "GET_EXCEPTION_VAR",
    "SET_EXCEPTION_VAR",
    "SET_EXCEPTION_UNDEF",
    "WEAKEN_FIELD",
    "UNWEAKEN_FIELD",
    "ISWEAK_FIELD",
    "REFCNT",
    "REFOP",
    "DUMP",
    "COPY",
    "GET_MULNUM_FIELD_BYTE",
    "GET_MULNUM_FIELD_SHORT",
    "GET_MULNUM_FIELD_INT",
    "GET_MULNUM_FIELD_LONG",
    "GET_MULNUM_FIELD_FLOAT",
    "GET_MULNUM_FIELD_DOUBLE",
    "SET_MULNUM_FIELD_BYTE",
    "SET_MULNUM_FIELD_SHORT",
    "SET_MULNUM_FIELD_INT",
    "SET_MULNUM_FIELD_LONG",
    "SET_MULNUM_FIELD_FLOAT",
    "SET_MULNUM_FIELD_DOUBLE",
    "MOVE_MULNUM_BYTE",
    "MOVE_MULNUM_SHORT",
    "MOVE_MULNUM_INT",
    "MOVE_MULNUM_LONG",
    "MOVE_MULNUM_FLOAT",
    "MOVE_MULNUM_DOUBLE",
    "GET_MULNUM_ARRAY_BYTE",
    "GET_MULNUM_ARRAY_SHORT",
    "GET_MULNUM_ARRAY_INT",
    "GET_MULNUM_ARRAY_LONG",
    "GET_MULNUM_ARRAY_FLOAT",
    "GET_MULNUM_ARRAY_DOUBLE",
    "SET_MULNUM_ARRAY_BYTE",
    "SET_MULNUM_ARRAY_SHORT",
    "SET_MULNUM_ARRAY_INT",
    "SET_MULNUM_ARRAY_LONG",
    "SET_MULNUM_ARRAY_FLOAT",
    "SET_MULNUM_ARRAY_DOUBLE",
    "GET_MULNUM_ARRAY_FIELD_BYTE",
    "GET_MULNUM_ARRAY_FIELD_SHORT",
    "GET_MULNUM_ARRAY_FIELD_INT",
    "GET_MULNUM_ARRAY_FIELD_LONG",
    "GET_MULNUM_ARRAY_FIELD_FLOAT",
    "GET_MULNUM_ARRAY_FIELD_DOUBLE",
    "SET_MULNUM_ARRAY_FIELD_BYTE",
    "SET_MULNUM_ARRAY_FIELD_SHORT",
    "SET_MULNUM_ARRAY_FIELD_INT",
    "SET_MULNUM_ARRAY_FIELD_LONG",
    "SET_MULNUM_ARRAY_FIELD_FLOAT",
    "SET_MULNUM_ARRAY_FIELD_DOUBLE",
    "DEREF_MULNUM_BYTE",
    "DEREF_MULNUM_SHORT",
    "DEREF_MULNUM_INT",
    "DEREF_MULNUM_LONG",
    "DEREF_MULNUM_FLOAT",
    "DEREF_MULNUM_DOUBLE",
    "GET_MULNUM_FIELD_DEREF_BYTE",
    "GET_MULNUM_FIELD_DEREF_SHORT",
    "GET_MULNUM_FIELD_DEREF_INT",
    "GET_MULNUM_FIELD_DEREF_LONG",
    "GET_MULNUM_FIELD_DEREF_FLOAT",
    "GET_MULNUM_FIELD_DEREF_DOUBLE",
    "SET_MULNUM_FIELD_DEREF_BYTE",
    "SET_MULNUM_FIELD_DEREF_SHORT",
    "SET_MULNUM_FIELD_DEREF_INT",
    "SET_MULNUM_FIELD_DEREF_LONG",
    "SET_MULNUM_FIELD_DEREF_FLOAT",
    "SET_MULNUM_FIELD_DEREF_DOUBLE",
    "GET_CLASS_ID",
    "GET_ERROR_CODE",
    "SET_ERROR_CODE",
    "CLEAR_BEFORE_ERROR",
    "GET_BEFORE_ERROR",
  };
  
  return id_names;
}

SPVM_OPCODE* SPVM_OPCODE_new(SPVM_COMPILER* compiler) {
  SPVM_OPCODE* opcode = SPVM_ALLOCATOR_alloc_memory_block_permanent(compiler->allocator, sizeof(SPVM_OPCODE));
  
  return opcode;
}

const char* SPVM_OPCODE_get_opcode_name(SPVM_COMPILER* compiler, int32_t opcode_id) {
  return (SPVM_OPCODE_C_ID_NAMES())[opcode_id];
}
