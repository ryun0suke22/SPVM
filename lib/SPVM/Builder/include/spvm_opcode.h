#ifndef SPVM_OPCODE_H
#define SPVM_OPCODE_H

#include "spvm_typedecl.h"






























































































enum {
  SPVM_OPCODE_C_ID_END_METHOD,
  SPVM_OPCODE_C_ID_ADD_INT,
  SPVM_OPCODE_C_ID_ADD_LONG,
  SPVM_OPCODE_C_ID_ADD_FLOAT,
  SPVM_OPCODE_C_ID_ADD_DOUBLE,
  SPVM_OPCODE_C_ID_SUBTRACT_INT,
  SPVM_OPCODE_C_ID_SUBTRACT_LONG,
  SPVM_OPCODE_C_ID_SUBTRACT_FLOAT,
  SPVM_OPCODE_C_ID_SUBTRACT_DOUBLE,
  SPVM_OPCODE_C_ID_MULTIPLY_INT,
  SPVM_OPCODE_C_ID_MULTIPLY_LONG,
  SPVM_OPCODE_C_ID_MULTIPLY_FLOAT,
  SPVM_OPCODE_C_ID_MULTIPLY_DOUBLE,
  SPVM_OPCODE_C_ID_DIVIDE_INT,
  SPVM_OPCODE_C_ID_DIVIDE_LONG,
  SPVM_OPCODE_C_ID_DIVIDE_FLOAT,
  SPVM_OPCODE_C_ID_DIVIDE_DOUBLE,
  SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_INT,
  SPVM_OPCODE_C_ID_DIVIDE_UNSIGNED_LONG,
  SPVM_OPCODE_C_ID_REMAINDER_INT,
  SPVM_OPCODE_C_ID_REMAINDER_LONG,
  SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_INT,
  SPVM_OPCODE_C_ID_REMAINDER_UNSIGNED_LONG,
  SPVM_OPCODE_C_ID_LEFT_SHIFT_INT,
  SPVM_OPCODE_C_ID_LEFT_SHIFT_LONG,
  SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_INT,
  SPVM_OPCODE_C_ID_RIGHT_ARITHMETIC_SHIFT_LONG,
  SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_INT,
  SPVM_OPCODE_C_ID_RIGHT_LOGICAL_SHIFT_LONG,
  SPVM_OPCODE_C_ID_BIT_AND_INT,
  SPVM_OPCODE_C_ID_BIT_AND_LONG,
  SPVM_OPCODE_C_ID_BIT_OR_INT,
  SPVM_OPCODE_C_ID_BIT_OR_LONG,
  SPVM_OPCODE_C_ID_BIT_XOR_INT,
  SPVM_OPCODE_C_ID_BIT_XOR_LONG,
  SPVM_OPCODE_C_ID_BIT_NOT_INT,
  SPVM_OPCODE_C_ID_BIT_NOT_LONG,
  SPVM_OPCODE_C_ID_NEGATE_INT,
  SPVM_OPCODE_C_ID_NEGATE_LONG,
  SPVM_OPCODE_C_ID_NEGATE_FLOAT,
  SPVM_OPCODE_C_ID_NEGATE_DOUBLE,
  SPVM_OPCODE_C_ID_INIT_BYTE,
  SPVM_OPCODE_C_ID_INIT_SHORT,
  SPVM_OPCODE_C_ID_INIT_INT,
  SPVM_OPCODE_C_ID_INIT_LONG,
  SPVM_OPCODE_C_ID_INIT_FLOAT,
  SPVM_OPCODE_C_ID_INIT_DOUBLE,
  SPVM_OPCODE_C_ID_INIT_UNDEF,
  SPVM_OPCODE_C_ID_INIT_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_INIT_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_INIT_MULNUM_INT,
  SPVM_OPCODE_C_ID_INIT_MULNUM_LONG,
  SPVM_OPCODE_C_ID_INIT_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_INIT_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_MOVE_CONSTANT_BYTE,
  SPVM_OPCODE_C_ID_MOVE_CONSTANT_INT,
  SPVM_OPCODE_C_ID_MOVE_CONSTANT_LONG,
  SPVM_OPCODE_C_ID_MOVE_CONSTANT_FLOAT,
  SPVM_OPCODE_C_ID_MOVE_CONSTANT_DOUBLE,
  SPVM_OPCODE_C_ID_MOVE_BYTE,
  SPVM_OPCODE_C_ID_MOVE_SHORT,
  SPVM_OPCODE_C_ID_MOVE_INT,
  SPVM_OPCODE_C_ID_MOVE_LONG,
  SPVM_OPCODE_C_ID_MOVE_FLOAT,
  SPVM_OPCODE_C_ID_MOVE_DOUBLE,
  SPVM_OPCODE_C_ID_MOVE_OBJECT,
  SPVM_OPCODE_C_ID_MOVE_OBJECT_WITH_TYPE_CHECKING,
  SPVM_OPCODE_C_ID_MOVE_OBJECT_CHECK_READ_ONLY,
  SPVM_OPCODE_C_ID_MOVE_UNDEF,
  SPVM_OPCODE_C_ID_MOVE_REF,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_STRING_TO_BYTE_ARRAY,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_ARRAY_TO_STRING,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_TO_BYTE_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_TO_SHORT_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_TO_INT_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_TO_LONG_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_TO_FLOAT_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_TO_DOUBLE_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_BYTE_OBJECT_TO_BYTE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_SHORT_OBJECT_TO_SHORT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_INT_OBJECT_TO_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_LONG_OBJECT_TO_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_FLOAT_OBJECT_TO_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_DOUBLE_OBJECT_TO_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_INT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_LONG,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_FLOAT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_DOUBLE,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_OBJECT,
  SPVM_OPCODE_C_ID_TYPE_CONVERSION_CONDITINAL_BOOL_OBJECT,
  SPVM_OPCODE_C_ID_CONCAT,
  SPVM_OPCODE_C_ID_EQ_INT,
  SPVM_OPCODE_C_ID_EQ_LONG,
  SPVM_OPCODE_C_ID_EQ_FLOAT,
  SPVM_OPCODE_C_ID_EQ_DOUBLE,
  SPVM_OPCODE_C_ID_EQ_OBJECT,
  SPVM_OPCODE_C_ID_NE_INT,
  SPVM_OPCODE_C_ID_NE_LONG,
  SPVM_OPCODE_C_ID_NE_FLOAT,
  SPVM_OPCODE_C_ID_NE_DOUBLE,
  SPVM_OPCODE_C_ID_NE_OBJECT,
  SPVM_OPCODE_C_ID_GT_INT,
  SPVM_OPCODE_C_ID_GT_LONG,
  SPVM_OPCODE_C_ID_GT_FLOAT,
  SPVM_OPCODE_C_ID_GT_DOUBLE,
  SPVM_OPCODE_C_ID_GE_INT,
  SPVM_OPCODE_C_ID_GE_LONG,
  SPVM_OPCODE_C_ID_GE_FLOAT,
  SPVM_OPCODE_C_ID_GE_DOUBLE,
  SPVM_OPCODE_C_ID_LT_INT,
  SPVM_OPCODE_C_ID_LT_LONG,
  SPVM_OPCODE_C_ID_LT_FLOAT,
  SPVM_OPCODE_C_ID_LT_DOUBLE,
  SPVM_OPCODE_C_ID_LE_INT,
  SPVM_OPCODE_C_ID_LE_LONG,
  SPVM_OPCODE_C_ID_LE_FLOAT,
  SPVM_OPCODE_C_ID_LE_DOUBLE,
  SPVM_OPCODE_C_ID_CMP_INT,
  SPVM_OPCODE_C_ID_CMP_LONG,
  SPVM_OPCODE_C_ID_CMP_FLOAT,
  SPVM_OPCODE_C_ID_CMP_DOUBLE,
  SPVM_OPCODE_C_ID_IS_UNDEF,
  SPVM_OPCODE_C_ID_IS_NOT_UNDEF,
  SPVM_OPCODE_C_ID_STRING_EQ,
  SPVM_OPCODE_C_ID_STRING_NE,
  SPVM_OPCODE_C_ID_STRING_GT,
  SPVM_OPCODE_C_ID_STRING_GE,
  SPVM_OPCODE_C_ID_STRING_LT,
  SPVM_OPCODE_C_ID_STRING_LE,
  SPVM_OPCODE_C_ID_STRING_CMP,
  SPVM_OPCODE_C_ID_GOTO,
  SPVM_OPCODE_C_ID_IF_EQ_ZERO,
  SPVM_OPCODE_C_ID_IF_NE_ZERO,
  SPVM_OPCODE_C_ID_IF_EXCEPTION_CATCH,
  SPVM_OPCODE_C_ID_IF_EXCEPTION_RETURN,
  SPVM_OPCODE_C_ID_LOOKUP_SWITCH,
  SPVM_OPCODE_C_ID_CASE_INFO,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_BYTE,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_SHORT,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_INT,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_LONG,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_FLOAT,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_DOUBLE,
  SPVM_OPCODE_C_ID_GET_ARRAY_ELEMENT_OBJECT,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_BYTE,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_SHORT,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_INT,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_LONG,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_FLOAT,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_DOUBLE,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_OBJECT_CHECK_TYPE,
  SPVM_OPCODE_C_ID_SET_ARRAY_ELEMENT_UNDEF,
  SPVM_OPCODE_C_ID_ARRAY_LENGTH,
  SPVM_OPCODE_C_ID_NEW_OBJECT,
  SPVM_OPCODE_C_ID_NEW_OBJECT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_MULTI_ARRAY,
  SPVM_OPCODE_C_ID_NEW_MULNUM_ARRAY,
  SPVM_OPCODE_C_ID_NEW_BYTE_ARRAY,
  SPVM_OPCODE_C_ID_NEW_SHORT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_INT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_LONG_ARRAY,
  SPVM_OPCODE_C_ID_NEW_FLOAT_ARRAY,
  SPVM_OPCODE_C_ID_NEW_DOUBLE_ARRAY,
  SPVM_OPCODE_C_ID_NEW_STRING,
  SPVM_OPCODE_C_ID_NEW_STRING_LEN,
  SPVM_OPCODE_C_ID_IS_READ_ONLY,
  SPVM_OPCODE_C_ID_MAKE_READ_ONLY,
  SPVM_OPCODE_C_ID_GET_FIELD_BYTE,
  SPVM_OPCODE_C_ID_GET_FIELD_SHORT,
  SPVM_OPCODE_C_ID_GET_FIELD_INT,
  SPVM_OPCODE_C_ID_GET_FIELD_LONG,
  SPVM_OPCODE_C_ID_GET_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_GET_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_GET_FIELD_OBJECT,
  SPVM_OPCODE_C_ID_SET_FIELD_BYTE,
  SPVM_OPCODE_C_ID_SET_FIELD_SHORT,
  SPVM_OPCODE_C_ID_SET_FIELD_INT,
  SPVM_OPCODE_C_ID_SET_FIELD_LONG,
  SPVM_OPCODE_C_ID_SET_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_SET_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_SET_FIELD_OBJECT,
  SPVM_OPCODE_C_ID_SET_FIELD_UNDEF,
  SPVM_OPCODE_C_ID_ISA,
  SPVM_OPCODE_C_ID_HAS_IMPL,
  SPVM_OPCODE_C_ID_ENTER_SCOPE,
  SPVM_OPCODE_C_ID_PUSH_MORTAL,
  SPVM_OPCODE_C_ID_LEAVE_SCOPE,
  SPVM_OPCODE_C_ID_PUSH_ARG_BYTE,
  SPVM_OPCODE_C_ID_PUSH_ARG_SHORT,
  SPVM_OPCODE_C_ID_PUSH_ARG_INT,
  SPVM_OPCODE_C_ID_PUSH_ARG_LONG,
  SPVM_OPCODE_C_ID_PUSH_ARG_FLOAT,
  SPVM_OPCODE_C_ID_PUSH_ARG_DOUBLE,
  SPVM_OPCODE_C_ID_PUSH_ARG_OBJECT,
  SPVM_OPCODE_C_ID_PUSH_ARG_REF,
  SPVM_OPCODE_C_ID_PUSH_ARG_UNDEF,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_INT,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_LONG,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_PUSH_ARG_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_CALL_CLASS_METHOD_BY_ID,
  SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_ID,
  SPVM_OPCODE_C_ID_CALL_INSTANCE_METHOD_BY_SIGNATURE,
  SPVM_OPCODE_C_ID_GET_ARG_BYTE,
  SPVM_OPCODE_C_ID_GET_ARG_SHORT,
  SPVM_OPCODE_C_ID_GET_ARG_INT,
  SPVM_OPCODE_C_ID_GET_ARG_LONG,
  SPVM_OPCODE_C_ID_GET_ARG_FLOAT,
  SPVM_OPCODE_C_ID_GET_ARG_DOUBLE,
  SPVM_OPCODE_C_ID_GET_ARG_OBJECT,
  SPVM_OPCODE_C_ID_GET_ARG_REF,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_INT,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_LONG,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_GET_ARG_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_RETURN_VOID,
  SPVM_OPCODE_C_ID_RETURN_BYTE,
  SPVM_OPCODE_C_ID_RETURN_SHORT,
  SPVM_OPCODE_C_ID_RETURN_INT,
  SPVM_OPCODE_C_ID_RETURN_LONG,
  SPVM_OPCODE_C_ID_RETURN_FLOAT,
  SPVM_OPCODE_C_ID_RETURN_DOUBLE,
  SPVM_OPCODE_C_ID_RETURN_OBJECT,
  SPVM_OPCODE_C_ID_RETURN_UNDEF,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_INT,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_LONG,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_RETURN_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_SET_ERROR,
  SPVM_OPCODE_C_ID_DIE,
  SPVM_OPCODE_C_ID_WARN,
  SPVM_OPCODE_C_ID_PRINT,
  SPVM_OPCODE_C_ID_REF,
  SPVM_OPCODE_C_ID_REF_BYTE,
  SPVM_OPCODE_C_ID_REF_SHORT,
  SPVM_OPCODE_C_ID_REF_INT,
  SPVM_OPCODE_C_ID_REF_LONG,
  SPVM_OPCODE_C_ID_REF_FLOAT,
  SPVM_OPCODE_C_ID_REF_DOUBLE,
  SPVM_OPCODE_C_ID_GET_DEREF_BYTE,
  SPVM_OPCODE_C_ID_GET_DEREF_SHORT,
  SPVM_OPCODE_C_ID_GET_DEREF_INT,
  SPVM_OPCODE_C_ID_GET_DEREF_LONG,
  SPVM_OPCODE_C_ID_GET_DEREF_FLOAT,
  SPVM_OPCODE_C_ID_GET_DEREF_DOUBLE,
  SPVM_OPCODE_C_ID_SET_DEREF_BYTE,
  SPVM_OPCODE_C_ID_SET_DEREF_SHORT,
  SPVM_OPCODE_C_ID_SET_DEREF_INT,
  SPVM_OPCODE_C_ID_SET_DEREF_LONG,
  SPVM_OPCODE_C_ID_SET_DEREF_FLOAT,
  SPVM_OPCODE_C_ID_SET_DEREF_DOUBLE,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_BYTE,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_SHORT,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_INT,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_LONG,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_FLOAT,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_DOUBLE,
  SPVM_OPCODE_C_ID_GET_CLASS_VAR_OBJECT,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_BYTE,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_SHORT,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_INT,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_LONG,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_FLOAT,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_DOUBLE,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_OBJECT,
  SPVM_OPCODE_C_ID_SET_CLASS_VAR_UNDEF,
  SPVM_OPCODE_C_ID_GET_EXCEPTION_VAR,
  SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR,
  SPVM_OPCODE_C_ID_SET_EXCEPTION_VAR_UNDEF,
  SPVM_OPCODE_C_ID_WEAKEN_FIELD,
  SPVM_OPCODE_C_ID_UNWEAKEN_FIELD,
  SPVM_OPCODE_C_ID_ISWEAK_FIELD,
  SPVM_OPCODE_C_ID_REFCNT,
  SPVM_OPCODE_C_ID_REFOP,
  SPVM_OPCODE_C_ID_DUMP,
  SPVM_OPCODE_C_ID_COPY,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_BYTE,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_SHORT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_INT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_LONG,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_BYTE,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_SHORT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_INT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_LONG,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_INT,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_LONG,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_MOVE_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_BYTE,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_SHORT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_INT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_LONG,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FLOAT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_DOUBLE,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_BYTE,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_SHORT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_INT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_LONG,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FLOAT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_DOUBLE,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_BYTE,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_SHORT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_INT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_LONG,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_GET_MULNUM_ARRAY_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_BYTE,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_SHORT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_INT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_LONG,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_FLOAT,
  SPVM_OPCODE_C_ID_SET_MULNUM_ARRAY_FIELD_DOUBLE,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_BYTE,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_SHORT,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_INT,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_LONG,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_FLOAT,
  SPVM_OPCODE_C_ID_DEREF_MULNUM_DOUBLE,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_BYTE,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_SHORT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_INT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_LONG,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_FLOAT,
  SPVM_OPCODE_C_ID_GET_MULNUM_FIELD_DEREF_DOUBLE,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_BYTE,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_SHORT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_INT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_LONG,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_FLOAT,
  SPVM_OPCODE_C_ID_SET_MULNUM_FIELD_DEREF_DOUBLE,
  SPVM_OPCODE_C_ID_GET_CLASS_ID,
  SPVM_OPCODE_C_ID_GET_ERROR_CODE,
  SPVM_OPCODE_C_ID_SET_ERROR_CODE,
  SPVM_OPCODE_C_ID_CLEAR_BEFORE_ERROR,
  SPVM_OPCODE_C_ID_GET_BEFORE_ERROR,
};

// Operation code is 64bit
struct spvm_opcode {
  uint16_t id;
  uint16_t operand3;
  uint32_t operand0;
  uint32_t operand1;
  uint32_t operand2;
};

SPVM_OPCODE* SPVM_OPCODE_new();
const char* const* SPVM_OPCODE_C_ID_NAMES(void);

const char* SPVM_OPCODE_get_opcode_name(SPVM_COMPILER* compiler, int32_t opcode_id);

#endif
