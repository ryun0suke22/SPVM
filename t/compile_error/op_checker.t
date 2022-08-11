use strict;
use warnings;
use utf8;
use FindBin;

use SPVM::Builder;

use lib "$FindBin::Bin/../default/lib";
use lib "$FindBin::Bin/lib";

use MyTest qw(compile_not_ok_file compile_not_ok);

use Test::More;

# Compilation Errors in spvm_op_checker.c 

# Array Initialization
{
  {
    my $source = 'class MyClass { static method main : void () { [undef]; } }';
    compile_not_ok($source, qr'The first element in the array initialization must be defined');
  }
}

# next
{
  {
    my $source = 'class MyClass { static method main : void () { { next; }; } }';
    compile_not_ok($source, qr'The next statement must be in a loop block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { next; }; } }';
    compile_not_ok($source, qr'The next statement must be in a loop block');
  }
}

# last
{
  {
    my $source = 'class MyClass { static method main : void () { { last; }; } }';
    compile_not_ok($source, qr'The last statement must be in a loop block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { last; }; } }';
    compile_not_ok($source, qr'The last statement must be in a loop block');
  }
}

# break
{
  {
    my $source = 'class MyClass { static method main : void () { { break; }; } }';
    compile_not_ok($source, qr'The break statement must be in a switch block');
  }
  {
    my $source = 'class MyClass { static method main : void () { if (1) { break; }; } }';
    compile_not_ok($source, qr'The break statement must be in a switch block');
  }
}

# refcnt
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; refcnt $num; } }';
    compile_not_ok($source, qr'The operand of the refcnt operator must be an object type');
  }
}

# ref
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; ref $num; } }';
    compile_not_ok($source, qr'The operand of the ref operator must be an object type');
  }
}

# dump
{
  {
    my $source = 'class MyClass { static method main : void () { my $num = 0; dump $num; } }';
    compile_not_ok($source, qr'The operand of the dump operator must be an object type');
  }
}

# class_id
{
  {
    my $source = 'class MyClass { static method main : void () { class_id NotExists; } }';
    compile_not_ok($source, qr'The operand of the class_id operator must be an existing class type. The class "NotExists" is not found');
  }
}

# set_error_code
{
  {
    my $source = 'class MyClass { static method main : void () { set_error_code 1d; } }';
    compile_not_ok($source, qr'The operand of the set_error_code operator must be the int type');
  }
}

# switch
{
  {
    my $source = 'class MyClass { static method main : void () { switch (1d) { } } }';
    compile_not_ok($source, qr'The condition of the switch statement must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case Int->new(1): { } } } }';
    compile_not_ok($source, qr'The operand of the case statement must be a constant value');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case "foo": { } } } }';
    compile_not_ok($source, qr'The operand of the case statement must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } case 1: { } } } }';
    compile_not_ok($source, qr"The value of the case statement can't be duplicated");
  }
  {
    my $source = 'class MyClass { static method main : void () { switch (1) { case 1: { } default: { } default: { } } } }';
    compile_not_ok($source, qr'Unexpected token "default"');
  }
}

# bool type conversion
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var_ref = \$var; !$var_ref; } }';
    compile_not_ok($source, qr'The operand of the bool type conversion must be one of a numeric type, an object type or the undef type');
  }
}

# ==
{
  {
    my $source = 'class MyClass { static method main : void () { undef == 1; } }';
    compile_not_ok($source, qr'The right operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == undef; } }';
    compile_not_ok($source, qr'The left operand of the == operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 == Int->new(1); } }';
    compile_not_ok($source, qr'The left and right operands of == operator must be numeric types or object types');
  }
}

# !=
{
  {
    my $source = 'class MyClass { static method main : void () { undef != 1; } }';
    compile_not_ok($source, qr'The right operand of the != operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 != undef; } }';
    compile_not_ok($source, qr'The left operand of the != operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 != Int->new(1); } }';
    compile_not_ok($source, qr'The left and right operands of != operator must be numeric types or object types');
  }
}

# >
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" > 1; } }';
    compile_not_ok($source, qr'The left operand of the > operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 > "foo"; } }';
    compile_not_ok($source, qr'The right operand of the > operator must be a numeric type');
  }
}

# >=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >= 1; } }';
    compile_not_ok($source, qr'The left operand of the >= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >= "foo"; } }';
    compile_not_ok($source, qr'The right operand of the >= operator must be a numeric type');
  }
}

# <
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" < 1; } }';
    compile_not_ok($source, qr'The left operand of the < operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 < "foo"; } }';
    compile_not_ok($source, qr'The right operand of the < operator must be a numeric type');
  }
}

# <=
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <= 1; } }';
    compile_not_ok($source, qr'The left operand of the <= operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <= "foo"; } }';
    compile_not_ok($source, qr'The right operand of the <= operator must be a numeric type');
  }
}

# <=>
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" <=> 1; } }';
    compile_not_ok($source, qr'The left operand of the <=> operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 <=> "foo"; } }';
    compile_not_ok($source, qr'The right operand of the <=> operator must be a numeric type');
  }
}

# gt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 gt "foo"; } }';
    compile_not_ok($source, 'The left operand of the gt operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" gt 1; } }';
    compile_not_ok($source, 'The right operand of the gt operator must be the string type or the byte[] type');
  }
}

# ge
{
  {
    my $source = 'class MyClass { static method main : void () { 1 ge "foo"; } }';
    compile_not_ok($source, 'The left operand of the ge operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" ge 1; } }';
    compile_not_ok($source, 'The right operand of the ge operator must be the string type or the byte[] type');
  }
}

# lt
{
  {
    my $source = 'class MyClass { static method main : void () { 1 lt "foo"; } }';
    compile_not_ok($source, 'The left operand of the lt operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" lt 1; } }';
    compile_not_ok($source, 'The right operand of the lt operator must be the string type or the byte[] type');
  }
}

# le
{
  {
    my $source = 'class MyClass { static method main : void () { 1 le "foo"; } }';
    compile_not_ok($source, 'The left operand of the le operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" le 1; } }';
    compile_not_ok($source, 'The right operand of the le operator must be the string type or the byte[] type');
  }
}

# cmp
{
  {
    my $source = 'class MyClass { static method main : void () { 1 cmp "foo"; } }';
    compile_not_ok($source, 'The left operand of the cmp operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" cmp 1; } }';
    compile_not_ok($source, 'The right operand of the cmp operator must be the string type or the byte[] type');
  }
}

# .
{
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) . "foo"; } }';
    compile_not_ok($source, 'The left operand of the . operator must be the string type or the byte[] type');
  }
  {
    my $source = 'class MyClass { static method main : void () { "foo" . Int->new(1); } }';
    compile_not_ok($source, 'The right operand of the . operator must be the string type or the byte[] type');
  }
}

# Capture
{
  {
    my $source = 'class MyClass { static method main : void () { [$foo : int] method : void () { }; } }';
    compile_not_ok($source, 'The capture variable "$foo" is not defined');
  }
}

# new
{
  {
    my $source = 'class MyClass { static method main : void () { new int[1L]; } }';
    compile_not_ok($source, 'The array length specified by the new operator must be the int type');
  }
  {
    my $source = 'class MyClass { static method main : void () { new int; } }';
    compile_not_ok($source, q|The operand of the new operator can't be a numeric type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () {  new Stringable; } }';
    compile_not_ok($source, q|The operand of the new operator can't be an interface type|);
  }
  {
    my $source = [
      'class MyClass { use MyPoint; static method main : void () { new MyPoint; } }',
      'class MyPoint : pointer_t;',
    ];
    compile_not_ok($source, q|The operand of the new operator can't be a pointer class type|);
  }
  {
    my $source = 'class MyClass { static method main : void () {  new Int; } }';
    compile_not_ok($source, q|The object can't be created from the private class|);
  }
}

# ^
{
  {
    my $source = 'class MyClass { static method main : void () { 1d ^ 1; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integral type');
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 ^ 1d; } }';
    compile_not_ok($source, 'The left and right operand of the ^ operator must be an integral type');
  }
}

# isa
{
  {
    my $source = 'class MyClass { static method main : void () { 1 isa Int; } }';
    compile_not_ok($source, 'The left operand of the isa operator must be an object type');
  }
}

# is_type
{
  {
    my $source = 'class MyClass { static method main : void () { 1 is_type Int; } }';
    compile_not_ok($source, 'The left operand of the is_type operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type int; } }';
    compile_not_ok($source, 'The right type of the is_type operator must be an object type');
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type object; } }';
    compile_not_ok($source, q|The right type of the is_type operator can't be the any object type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { Int->new(1) is_type object[]; } }';
    compile_not_ok($source, q|The right type of the is_type operator can't be the any object array type|);
  }
  {
    my $source = 'class MyClass { use Stringable; static method main : void () { Int->new(1) is_type Stringable; } }';
    compile_not_ok($source, q|The right type of the is_type operator can't be an interface type|);
  }
}

# @ - Array Length
{
  {
    my $source = 'class MyClass { static method main : void () { @1; } }';
    compile_not_ok($source, 'The right operand of the @ operator must be an array type');
  }
}

# length
{
  {
    my $source = 'class MyClass { static method main : void () { length new int[3]; } }';
    compile_not_ok($source, 'The operand of the length operator must be the string type');
  }
}

# ++,-- Increment, Decrement
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var++; } }';
    compile_not_ok($source, 'The operand of the increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; ++$var; } }';
    compile_not_ok($source, 'The operand of the increment operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $var--; } }';
    compile_not_ok($source, 'The operand of the decrement operator must be a numeric type');
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; --$var; } }';
    compile_not_ok($source, 'The operand of the decrement operator must be a numeric type');
  }
  
}

# = Assignment
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = undef; } }';
    compile_not_ok($source, q|The type of "$var" can't be detected|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var : byte = "string"; } }';
    compile_not_ok($source, q|The implicite type conversion from "string" to "byte" in the assignment operator is not allowed|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = "string"; $var->[0] = \'a\'; } }';
    compile_not_ok($source, q|Characters cannot be set to non-mutable strings|);
  }
}

# return
{
  {
    my $source = 'class MyClass { static method main : void () { return 1; } }';
    compile_not_ok($source, q|The void method can't return the value|);
  }
  {
    my $source = 'class MyClass { static method main : int () { return; } }';
    compile_not_ok($source, q|The non-void method must return a value|);
  }
}

# + Unary Plus
{
  {
    my $source = 'class MyClass { static method main : void () { +"foo"; } }';
    compile_not_ok($source, q|The operand of the unary + operator must be a numeric type|);
  }
}

# - Unary Minus
{
  {
    my $source = 'class MyClass { static method main : void () { -"foo"; } }';
    compile_not_ok($source, q|The operand of the unary - operator must be a numeric type|);
  }
}

# copy
{
  {
    my $source = 'class MyClass { static method main : void () { copy 1; } }';
    compile_not_ok($source, q|The operand of the copy operator must be an object type|);
  }
}

# ~ Bit Not
{
  {
    my $source = 'class MyClass { static method main : void () { ~ 1d; } }';
    compile_not_ok($source, q|The operand of the ~ operator must be an integral type|);
  }
}

# + Addition
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" + 1; } }';
    compile_not_ok($source, q|The left operand of the + operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 + "foo"; } }';
    compile_not_ok($source, q|The right operand of the + operator must be a numeric type|);
  }
}

# - Subtract
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" - 1; } }';
    compile_not_ok($source, q|The left operand of the - operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 - "foo"; } }';
    compile_not_ok($source, q|The right operand of the - operator must be a numeric type|);
  }
}

# * Multiplication
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" * 1; } }';
    compile_not_ok($source, q|The left operand of the * operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 * "foo"; } }';
    compile_not_ok($source, q|The right operand of the * operator must be a numeric type|);
  }
}

# / Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" / 1; } }';
    compile_not_ok($source, q|The left operand of the / operator must be a numeric type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 / "foo"; } }';
    compile_not_ok($source, q|The right operand of the / operator must be a numeric type|);
  }
}

# divui
{
  {
    my $source = 'class MyClass { static method main : void () { 1L divui 1; } }';
    compile_not_ok($source, q|The left operand of the divui operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 divui 1L; } }';
    compile_not_ok($source, q|The right operand of the divui operator must be the int type|);
  }
}

# divul
{
  {
    my $source = 'class MyClass { static method main : void () { 1 divul 1L; } }';
    compile_not_ok($source, q|The left operand of the divul operator must be the long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L divul 1; } }';
    compile_not_ok($source, q|The right operand of the divul operator must be the long type|);
  }
}

# % Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" % 1; } }';
    compile_not_ok($source, q|The left operand of the % operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 % "foo"; } }';
    compile_not_ok($source, q|The right operand of the % operator must be an integral type|);
  }
}

# remui
{
  {
    my $source = 'class MyClass { static method main : void () { 1L remui 1; } }';
    compile_not_ok($source, q|The left operand of the remui operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 remui 1L; } }';
    compile_not_ok($source, q|The right operand of the remui operator must be the int type|);
  }
}

# remul
{
  {
    my $source = 'class MyClass { static method main : void () { 1 remul 1L; } }';
    compile_not_ok($source, q|The left operand of the remul operator must be the long type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1L remul 1; } }';
    compile_not_ok($source, q|The right operand of the remul operator must be the long type|);
  }
}

# & Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" & 1; } }';
    compile_not_ok($source, q|The left operand of the & operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 & "foo"; } }';
    compile_not_ok($source, q|The right operand of the & operator must be an integral type|);
  }
}

# | Division
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" | 1; } }';
    compile_not_ok($source, q|The left operand of the \| operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 | "foo"; } }';
    compile_not_ok($source, q|The right operand of the \| operator must be an integral type|);
  }
}

# << Left Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" << 1; } }';
    compile_not_ok($source, q|The left operand of the << operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1d; } }';
    compile_not_ok($source, q|The right operand of the << operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 << 1L; } }';
    compile_not_ok($source, q|The right operand of the << operator must be the int type|);
  }
}

# >> Right Arithmetic Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >> 1; } }';
    compile_not_ok($source, q|The left operand of the >> operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1d; } }';
    compile_not_ok($source, q|The right operand of the >> operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >> 1L; } }';
    compile_not_ok($source, q|The right operand of the >> operator must be the int type|);
  }
}

# >>> Right Logical Shift
{
  {
    my $source = 'class MyClass { static method main : void () { "foo" >>> 1; } }';
    compile_not_ok($source, q|The left operand of the >>> operator must be an integral type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1d; } }';
    compile_not_ok($source, q|The right operand of the >>> operator must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { 1 >>> 1L; } }';
    compile_not_ok($source, q|The right operand of the >>> operator must be the int type|);
  }
}

# die
{
  {
    my $source = 'class MyClass { static method main : void () { die Int->new(1); } }';
    compile_not_ok($source, q|The implicite type conversion from "Int" to "string" in the assignment operator is not allowed|);
  }
}

# warn
{
  {
    my $source = 'class MyClass { static method main : void () { warn Int->new(1); } }';
    compile_not_ok($source, q|The operand of the warn statement must be the string type|);
  }
}

# print
{
  {
    my $source = 'class MyClass { static method main : void () { print Int->new(1); } }';
    compile_not_ok($source, q|The operand of the print statement must be the string type|);
  }
}

# make_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { make_read_only 1; } }';
    compile_not_ok($source, q|The operand of the make_read_only statement must be the string type|);
  }
}

# is_read_only
{
  {
    my $source = 'class MyClass { static method main : void () { is_read_only 1; } }';
    compile_not_ok($source, q|The operand of the is_read_only operator must be the string type|);
  }
}

# Reference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; \$var; } }';
    compile_not_ok($source, q|The operand of the refernece operator must be a numeric type or a multi-numeric type|);
  }
}

# Dereference
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = "foo"; $$var; } }';
    compile_not_ok($source, q|The operand of the dereference operaotr must be a numeric reference type or a multi-numeric reference type|);
  }
}

# Variable
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; my $var = 0; } }';
    compile_not_ok($source, q|Redeclaration of the variable "$var"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var; } }';
    compile_not_ok($source, q|The type of the variable "$var" must be defined|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $var; } }';
    compile_not_ok($source, q|The variable "$var" is not defined|);
  }
  {
    my $source = 'class MyClass { static method main : void () { $MyClass::FOO; } }';
    compile_not_ok($source, q|The variable "$MyClass::FOO" is not defined|);
  }
}

# Method Call
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = Int->new(1); $var->new; } }';
    compile_not_ok($source, q|The instance method "new" in the class "Int" is not defined|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { MyClass2->foo();  } }',
      'class MyClass2 { static private method foo : void () {} }'
    ];
    compile_not_ok($source, q|The private method "foo" can't be called|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo(); } static method foo : void ($arg0 : int, $arg1 = 0 : int) { } }';
    compile_not_ok($source, q|The length of the arguments passed to the class method "foo" in the class "MyClass" must be at least 1|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(); } method foo : void ($arg0 : int, $arg1 = 0 : int) { } }';
    compile_not_ok($source, q|The length of the arguments passed to the instance method "foo" in the class "MyClass" must be at least 1|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo(1, 2, 3); } method foo : void ($arg0 : int, $arg1 = 0 : int) { } }';
    compile_not_ok($source, q|The length of the arguments passed to the instance method "foo" in the class "MyClass" must be less than or equal to 2|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->DESTROY; } method DESTROY : void () {} }';
    compile_not_ok($source, q|The DESTROY method can't be called|);
  }
}

# Class Variable Access
{
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { $MyClass2::FOO;  } }',
      'class MyClass2 { our $FOO : private int; }'
    ];
    compile_not_ok($source, q|The private class variable "$MyClass2::FOO" can't be accessed|);
  }
}

# Array Access
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->[0]; } }';
    compile_not_ok($source, q|The invocant of the array access must be an array type or the string type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->[1L]; } }';
    compile_not_ok($source, q|The index of the array access must be the int type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $var = new int[1]; $var->["foo"]; } }';
    compile_not_ok($source, q|The index of the array access must be the int type|);
  }
}

# Field Access
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 1; $var->{x}; } }';
    compile_not_ok($source, q|The invocant of the field access must be a class type, or a multi-numeric type, or a multi-numeric reference type|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->{foo}; } }';
    compile_not_ok($source, q|The field "foo" in the class "MyClass" is not defined|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; weaken $object->{x}; } }';
    compile_not_ok($source, q|The field "x" in the class "MyClass" operated by the weaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; unweaken $object->{x}; } }';
    compile_not_ok($source, q|The field "x" in the class "MyClass" operated by the unweaken operator must be an object type|);
  }
  {
    my $source = 'class MyClass { has x : int; static method main : void () { my $object = new MyClass; isweak $object->{x}; } }';
    compile_not_ok($source, q|The field "x" in the class "MyClass" operated by the isweak operator must be an object type|);
  }
  {
    my $source = [
      'class MyClass { use MyClass2; static method main : void () { my $object = new MyClass2; $object->{x};  } }',
      'class MyClass2 : public { has x : private int; }'
    ];
    compile_not_ok($source, q|The private field "x" in the class "MyClass2" can't be accessed|);
  }
}

# has_impl
{
  {
    my $source = 'class MyClass { static method main : void () { my $var = 0; has_impl $var->x; } }';
    compile_not_ok($source, q|he invocant of the has_impl operator must be a class type or an interface type|);
  }
  {
    my $source = 'class MyClass { use Point; static method main : void () { my $point = Point->new; has_impl $point->not_defined; } }';
    compile_not_ok($source, q|The method "not_defined" in the class "Point" checked by the has_impl operator must be defined|);
  }
  
}

# Type Case
{
  {
    my $source = 'class MyClass { static method main : void () { (Int)"foo"; } }';
    compile_not_ok($source, q|The type cast from "string" to "Int" is not allowed|);
  }
}

# Assignability
{
  {
    my $source = 'class MyClass { static method main : void () { my $string : mutable string = "abc"; } }';
    compile_not_ok($source, q|The non-mutable type can't be assign to a mutable type in the assignment operator|);
  }
  {
    my $source = 'class MyClass { static method main : mutable string () { return "abc"; } }';
    compile_not_ok($source, q|The non-mutable type can't be assign to a mutable type in the return statement|);
  }
  {
    my $source = 'class MyClass { static method main : void () { &foo("abc"); } static method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|The non-mutable type can't be assign to a mutable type in the 1th argument of the class method "foo" in the class "MyClass"|);
  }
  {
    my $source = 'class MyClass { static method main : void () { my $object = new MyClass; $object->foo("abc"); } method foo : int ($string : mutable string) { }}';
    compile_not_ok($source, q|The non-mutable type can't be assign to a mutable type in the 1th argument of the instance method "foo" in the class "MyClass"|);
  }
}
done_testing;