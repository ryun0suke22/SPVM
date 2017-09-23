#include <assert.h>
#include <stdio.h>
#include <stdint.h>
#include <inttypes.h>
#include <math.h>

#include "spvm_api.h"

double SPVM__Math__sin(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = sin(args[0].double_value);
  
  return value;
}

double SPVM__Math__cos(SPVM_API* api, SPVM_API_VALUE* args) {
  (void)api;
  
  double value = cos(args[0].double_value);
  
  return value;
}

