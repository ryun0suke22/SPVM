use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use SPVM 'TestCase::ConditionalBranch';

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();

# Conditional Branch
#   if Statement
#   elsif Statement
#   else Statement
#   unless Statement
{
  ok(SPVM::TestCase::ConditionalBranch->if_condition_types());
  ok(SPVM::TestCase::ConditionalBranch->if_condition_true());
  ok(SPVM::TestCase::ConditionalBranch->if_condition_false());
  ok(SPVM::TestCase::ConditionalBranch->elsif_condition_true());
  ok(SPVM::TestCase::ConditionalBranch->elsif_condition_false());
  ok(SPVM::TestCase::ConditionalBranch->elsif_only());
  ok(SPVM::TestCase::ConditionalBranch->else_only());
  ok(SPVM::TestCase::ConditionalBranch->if_condition_my());
}

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
