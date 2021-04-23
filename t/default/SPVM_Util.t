use lib "t/lib";
use TestAuto;

use strict;
use warnings;

use Test::More 'no_plan';

use SPVM 'TestCase::Lib::SPVM::Util';
use SPVM 'SPVM::Util';
use POSIX();
use TestFile;

# Start objects count
my $start_memory_blocks_count = SPVM::get_memory_blocks_count();

my $BYTE_MAX = 127;
my $BYTE_MIN = -128;
my $SHORT_MAX = 32767;
my $SHORT_MIN = -32768;
my $INT_MAX = 2147483647;
my $INT_MIN = -2147483648;
my $LONG_MAX = 9223372036854775807;
my $LONG_MIN = -9223372036854775808;
my $FLOAT_PRECICE = 16384.5;
my $DOUBLE_PRECICE = 65536.5;

# Positive infinity(unix like system : inf, Windows : 1.#INF)
my $POSITIVE_INFINITY = 9**9**9;

my $NaN = 9**9**9 / 9**9**9;

my $nan_re = qr/(nan|ind)/i;

use SPVM 'TestCase::Lib::SPVM::Util';
use SPVM 'SPVM::Util';

# crand
{
  ok(TestCase::Lib::SPVM::Util->test_crand);
}

# rand
{
  ok(TestCase::Lib::SPVM::Util->test_rand);
}

# srand
SKIP: {
  if ($^O eq 'openbsd') {
    skip "openbsd srand don't fllow POSIX", 6;
  }
  
  {
    ok(TestCase::Lib::SPVM::Util->test_srand);
  }
}

# RAND_MAX
{
  ok(TestCase::Lib::SPVM::Util->test_RAND_MAX);
}

# Copy
{
  # copy_string
  ok(TestCase::Lib::SPVM::Util->test_copy_str);
}

# Constant integral functions
{
  is(SPVM::Util->INT8_MAX, 127);
  is(SPVM::Util->INT8_MIN, -128);
  is(SPVM::Util->INT16_MAX, 32767);
  is(SPVM::Util->INT16_MIN, -32768);
  is(SPVM::Util->INT32_MAX, 2147483647);
  is(SPVM::Util->INT32_MIN, -2147483648);
  is(SPVM::Util->INT64_MAX, 9223372036854775807);
  is(SPVM::Util->INT64_MIN, -9223372036854775808);
  is(SPVM::Util->UINT8_MAX, -1);
  is(SPVM::Util->UINT16_MAX, -1);
  is(SPVM::Util->UINT32_MAX, -1);
  is(SPVM::Util->UINT64_MAX, -1);
}

# Constant floating point number functions
{
  is(SPVM::Util->FLT_MAX, POSIX::FLT_MAX);
  is(SPVM::Util->FLT_MIN, POSIX::FLT_MIN);
  is(SPVM::Util->DBL_MAX, POSIX::DBL_MAX);
  is(SPVM::Util->DBL_MIN, POSIX::DBL_MIN);
}

{
  ok(TestCase::Lib::SPVM::Util->test_byte_constant);
  ok(TestCase::Lib::SPVM::Util->test_short_constant);
  ok(TestCase::Lib::SPVM::Util->test_int_constant);
}

{
  is(SPVM::Util->INT8_MAX, $BYTE_MAX);
  is(SPVM::Util->INT8_MIN, $BYTE_MIN);
  is(SPVM::Util->INT16_MAX, $SHORT_MAX);
  is(SPVM::Util->INT16_MIN, $SHORT_MIN);
  is(SPVM::Util->INT32_MAX, $INT_MAX);
  is(SPVM::Util->INT32_MIN, $INT_MIN);
  is(SPVM::Util->INT64_MAX, $LONG_MAX);
  is(SPVM::Util->INT64_MIN, $LONG_MIN);
}
{
  # Check not Inf or NaN in Perl value
  like(SPVM::Util->FLT_MAX(), qr/[0-9]/);
  like(SPVM::Util->FLT_MIN(), qr/[0-9]/);
}

# All object is freed
my $end_memory_blocks_count = SPVM::get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);
