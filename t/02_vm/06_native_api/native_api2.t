use lib "t/testlib";
use TestAuto;

use strict;
use warnings;

use Test::More;

use Config;
use Errno;

use SPVM 'TestCase::NativeAPI2';

my $build_dir = $ENV{SPVM_BUILD_DIR};

# Start objects count
my $start_memory_blocks_count = SPVM::api->get_memory_blocks_count();


# Native Exception
{
  is(SPVM::TestCase::NativeAPI2->mul(2, 3), 6);
  ok(SPVM::TestCase::NativeAPI2->spvm_extension2);
}

# src and include directory
{
  ok(SPVM::TestCase::NativeAPI2->src_foo);
  ok(SPVM::TestCase::NativeAPI2->src_bar);
}

{
  my $link_info = $main::NATIVE_API2_LINK_INFO;
  
  my $config = SPVM::Builder::Config->new_gnu99(file_optional => 1);
  
  ok($link_info->class_name, 'TestCase::NativeAPI2');
  ok($link_info->ld, $config->ld);
  ok($link_info->ldflags, $config->ldflags);
  like($link_info->output_file, qr|TestCase/NativeAPI2\.$Config{dlext}|);
  my $is_object_file_infos = 1;
  for my $object_file_info (@{$link_info->object_file_infos}) {
    unless ($object_file_info->isa('SPVM::Builder::ObjectFileInfo')) {
      $is_object_file_infos = 0;
    }
  }
  ok($is_object_file_infos);
}

# Clear exception
SPVM::api->set_exception(undef);

# All object is freed
my $end_memory_blocks_count = SPVM::api->get_memory_blocks_count();
is($end_memory_blocks_count, $start_memory_blocks_count);

done_testing;
