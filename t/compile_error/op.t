use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok);

use Test::More;

# Compilation Errors in spvm_op.c 

# Class Name
{
  {
    my $source = 'class MyClass { static method main : void () { {"foo" => 1, "bar"}; } }';
    compile_not_ok($source, qr/\QThe lenght of the elements in {} of the array initialization must be an even number/);
  }
}

done_testing;
