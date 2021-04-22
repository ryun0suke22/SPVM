package SPVM::Util;

1;

=head1 NAME

SPVM::Util - Variouse utilities

=head1 SYNOPSYS
  
  use SPVM::Util (chomp_lf, chomp_crlf);

  # Cut a newline LF
  {
    my $ret = chomp_lf("abc\n");
  }
  
  # Cut a newline CR LF
  {
    my $ret = chomp_crlf("abc\r\n");
  }
  
  # Create a new float complex array
  {
    my $re_values = [1.5f, 2.5f, 3.5f];
    my $im_values = [5.5f, 6.5f, 7.5f];
    my $farray = complex_float_array($re_values, $im_values);
  }

  # Create a new double complex array
  {
    my $re_values = [1.5, 2.5, 3.5];
    my $im_values = [5.5, 6.5, 7.5];
    my $farray = complex_double_array($re_values, $im_values);
  }
  
  # Create a new float complex value
  {
    my $z = complexf(1.5f, 2.5f);
  }

  # Create a new double complex value
  {
    my $z = complexd(1.5f, 2.5f);
  }
  
  # Copy a byte array
  {
    my $nums = [(byte)1, 2, 3];
    my $nums_copy = copy_byte_array($nums);
  }

  # Copy a string
  {
    my $str = "abc";
    my $str_copy = copy_str($str);
  }

  # Copy a short array
  {
    my $nums = [(short)1, 2, 3];
    my $nums_copy = copy_short_array($nums);
  }

  # Copy a int array
  {
    my $nums = [1, 2, 3];
    my $nums_copy = copy_int_array($nums);
  }

  # Copy a long array
  {
    my $nums = [(long)1, 2, 3];
    my $nums_copy = copy_long_array($nums);
  }

  # Copy a float array
  {
    my $nums = [1.5f, 2.5f, 3.5f];
    my $nums_copy = copy_float_array($nums);
  }

  # Copy a double array
  {
    my $nums = [1.5, 2.5, 3.5];
    my $nums_copy = copy_double_array($nums);
  }
  
  # Copy a string array
  {
    my $strs = ["abc", "def", "ghi"]
    my $strs_copy = copy_string_array($strs);
  }
  
  # Check if the two byte arrays equal
  {
    my $nums1 = [(byte)1, 2];
    my $nums2 = [(byte)1, 2];
    my $ret = equals_byte_array($nums1, $nums2);
  }

  # Check if the two short arrays equal
  {
    my $nums1 = [(short)1, 2];
    my $nums2 = [(short)1, 2];
    my $ret = equals_short_array($nums1, $nums2);
  }

  # Check if the two int arrays equal
  {
    my $nums1 = [(int)1, 2];
    my $nums2 = [(int)1, 2];
    my $ret = equals_int_array($nums1, $nums2);
  }

  # Check if the two long arrays equal
  {
    my $nums1 = [(long)1, 2];
    my $nums2 = [(long)1, 2];
    my $ret = equals_long_array($nums1, $nums2);
  }

  # Check if the two float arrays equal
  {
    my $nums1 = [(float)1, 2];
    my $nums2 = [(float)1, 2];
    my $ret = equals_float_array($nums1, $nums2);
  }

  # Check if the two double arrays equal
  {
    my $nums1 = [(double)1, 2];
    my $nums2 = [(double)1, 2];
    my $ret = equals_double_array($nums1, $nums2);
  }

  # Check if the two string arrays equal
  {
    my $strs1 = ["abc", "def"];
    my $strs2 = ["abc", "def"];
    my $ret = equals_string_array($strs1, $strs2);
  }
  
  # Search substr
  {
    my $found_offset = index("pppabcde", "bcd", 2);
  }

  # Copy object array
  my $objects = [(object)SPVM::Int->new(1), SPVM::Int->new(2), SPVM::Int->new(3)];
  my $objects_copy = copy_object_array($objects, sub : object ($self : self, $obj : object) {
    my $int_obj = (SPVM::Int)$obj;
    my $new_int_obj = SPVM::Int->new($int_obj->value);
    return $new_int_obj;
  });
  
  # Stringify all object and join them by the specific separator
  my $objects = new Foo[3];
  my $str = SPVM::Util->join_object(",", $objects, sub : string ($self : self, $obj : object) {
    my $point = (SPVM::Point)$obj;
    my $x = $point->x;
    my $y = $point->y;
    
    my $str = "($x, $y)";
    
    return $str;
  });
  
  # split a string by the specific separator
  my $str = "foo,bar,baz";
  my $splited_strs = split(",", $str);

=head1 DESCRIPTION

Unix standard library.

=head1 STATIC METHODS

=head2 join_object

  sub join_object : string ($sep : string, $objects : oarray, $stringer : SPVM::Stringer)

Stringify all objects and join them by specific separator.
You must specify a L<SPVM::Stringer> object to stringify each element.

If separater is undef, a exception occurs.

If object array is undef, a exception occurs.

=head2 split

  sub split : string[] ($sep : string, $string : string)

Split a string by the specific separator.

=head2 chomp_lf

  sub chomp_lf : string ($string : string)

Copy the string and remove the newline "\n" from the end of string and return it.

=head2 chomp_crlf

  sub chomp_crlf : string ($string : string)

Copy the string and remove the newline "\r\n" from the end of string and return it.

=head2 copy_str

  sub copy_str : string ($string : string)

Copy a string.

If the array is undefined, a exception occurs.

=head2 index

  sub index : int ($str : string, $substr : string, $posision : int)

index function searches for one string within another.
It returns the position of the first occurrence of $substr in $str at or after $position. If $position is omitted, starts
searching from the beginning of the string. $position before the
beginning of the string or after its end is treated as if it were
the beginning or the end, respectively. $position and the return
value are based at zero. If the substring is not found, "index"
returns -1.
            
=head2 INT8_MIN

  sub INT8_MIN : byte ()

byte(8bit integer) min value. return -128.

=head2 INT8_MAX

  INT8_MAX : byte ()

byte(8bit integer) max value. return 127.

=head2 INT16_MIN

  sub INT16_MIN : short ()

short(16bit integer) min value. return -32768.

=head2 INT16_MAX

  sub INT16_MAX : short ()

short(16bit integer) max value. return 32767.

=head2 INT32_MIN

  sub INT32_MIN : int ()

int(32bit integer) min value. return -2147483648.

=head2 INT32_MAX

  sub INT32_MAX : int ()

int(32bit integer) max value. return 2147483647.

=head2 INT64_MIN

  sub INT64_MIN : long ()

long(64bit integer) min value. return -9223372036854775808.

=head2 INT64_MAX

  sub INT64_MAX : long ()

long(64bit integer) max value. return 9223372036854775807.

=head2 UINT8_MAX

  sub UINT8_MAX : byte ()

return -1. This is same as bit expression of 0xFF in unsigned 8bit integer in 2's complement.

=head2 UINT16_MAX

  sub UINT16_MAX : short ()

return -1. This is same as bit expression of 0xFFFF in unsigned 8bit integer in 2's complement.

=head2 UINT32_MAX

  sub UINT32_MAX : int ()

return -1. This is same as bit expression of 0xFFFFFFFF in unsigned 8bit integer in 2's complement.

=head2 UINT64_MAX

  sub UINT64_MAX : long ()

return -1. This is same as bit expression of 0xFFFFFFFFFFFFFFFF in unsigned 8bit integer in 2's complement.

=head2 FLT_MIN

  sub FLT_MIN : float ()

return the value of FLT_MIN macro of float.h C library.

=head2 FLT_MAX

  sub FLT_MAX : float ()

return the value of FLT_MAX macro of float.h C library.

=head2 DBL_MIN

  sub DBL_MIN : double ()

return the value of DBL_MIN macro of float.h C library.

=head2 DBL_MAX

  sub DBL_MAX : double ()

return the value of DBL_MAX macro of float.h C library.

=head2 isalnum

  sub isalnum : int ($char : int)

If character is alphanumeric('A'-'Z', 'a'-'z', '0'-'9'), return 1. If not, return 0.

=head2 isalpha

  sub isalpha : int ($char : int)

If character is alphabetic('A'-'Z', 'a'-'z'), return 1. If not, return 0.

=head2 isblank

  sub isblank : int ($char : int)

If character is blank(' ', '\t'), return 1. If not, return 0.

=head2 iscntrl

  sub iscntrl : int ($char : int)

If character is a control character(0x00-0x1F, 0x7F), return 1. If not, return 0.

=head2 isdigit

  sub isdigit : int ($char : int)

If character is decimal digit ('0'～'9'), return 1. If not, return 0.

=head2 isgraph

  sub isgraph : int ($char : int)

If character has graphical representation(0x21-0x7E), return 1. If not, return 0.

=head2 islower

  sub islower : int ($char : int)

If character is lowercase letter('a'-'z'), return 1. If not, return 0.

=head2 isprint

  sub isprint : int ($char : int)

If character is printable(0x20-0x7E), return 1. If not, return 0.

=head2 ispunct

  sub ispunct : int ($char : int)

If character is a punctuation character(0x21-0x2f, 0x3a-0x40, 0x5b-0x60, 0x7b-0x7e), return 1. If not, return 0.

=head2 isspace

  sub isspace : int ($char : int)

If character is a white-space(' ',  '\t', '\n', '\v', '\f', '\r'), return 1. If not, return 0.

=head2 isupper

  sub isupper : int ($char : int)

If character is uppercase letter('A'-'Z'), return 1. If not, return 0.

=head2 isxdigit

  sub isxdigit : int ($char : int)

If character is hexadecimal digit('0'-'9', 'A'-'F', 'a'-'f'), return 1. If not, return 0.

=head2 tolower

  sub tolower : int ($char : int)

Convert uppercase letter('A'-'Z') to lowercase. If the character is not uppercase letter, return the character.

=head2 toupper

  sub toupper : int ($char : int)

Convert lowercase letter('a'-'z') to lowercase. If the character is not uppercase letter, return the character.

=head2 is_perl_space

  sub is_perl_space : int ($char : int)

If character is Perl space character(' ', '\r', '\n', '\t', '\f'), return 1. If not, return 0.

=head2 is_perl_word

  sub is_perl_word : int ($char : int)

If character is Perl word character('a'-'z', 'A'-'Z', '_', '0'-'9'), return 1. If not, return 0.

=head2 join

  sub join : string ($sep : string, $strings : string[])
  
Join a string array with separater and return it.

If separater is undef, a exception occurs.

If string array is undef, a exception occurs.

=head2 lc

  sub lc : string($str : string)

Convert uppercase string to lowercase string.

=head2 lcfirst

  sub lcfirst : string($str : string)

Convert first chracter of string from uppercase to lowercase.

=head2 crand

  sub crand : int ();

Get random number(0 to SPVM::Util->RAND_MAX). This is same as rand function of C language.

The first seed is epoch time usually. Second seed is the return value.

  use SPVM::Time;
  my $rand1 = crand(SPVM::Time->time);
  my $rand2 = crand($rand1);

=head2 rand

  sub rand : double ();

Get random number(0 <= random_number < 1). This is same as rand function of Perl language.

The first seed is epoch time usually. Second seed is the return value.

  use SPVM::Time;
  my $rand1 = crand(SPVM::Time->time);
  my $rand2 = crand($rand1);

=head2 srand

  sub srand : void ($seed : long);

Sets random number seed for the "crand" static method.

=head2 replace

  sub replace : string ($str : string, $substr : string, $replace : string, $start_offset : int, $found_offset_ref : int&)

Replace the sub string in the string with a replace string and return the result string.

You can specify a byte offset of the string.

You can get the found byte offset by int reference.

  my $str = "abcde";
  my $substr = "bcd";
  my $replace = "AB";
  my $found_offset = 0;
  my $result_str = replace($str, $substr, $replace, 0, \$found_offset);

=head2 replace_all

  sub replace_all : string ($str : string, $substr : string, $replace : string)

Replace all the sub string in the string with a replace string and return the result string.

  my $str = "foo bar foo bar foo";
  my $substr = "bar";
  my $replace = "AB";
  my $result_str = replace_all($str, $substr, $replace);

=head2 strtoi

  sub strtoi : int ($string : string, $digit : int);

Convert the string to a int value with a digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][one more than 0-9]. Internal of [] is optional.

If convertion fails, a exception occuer.

  my $string = "-2147483648";
  my $num = strtoi($string, 10);

=head2 strtol

  sub strtol : long ($string : string, $digit : int);

Convert the string to long value with digit(2, 8, 10, 16).

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][0][x][zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "-9223372036854775808";
  my $num = strtol($string, 10);

=head2 strtof

  sub strtof : float ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = strtof($string);

=head2 strtod

  sub strtod : double ($string : string);

Convert the string to float value.

Format is [' ' or '\t' or '\n' or '\v' or '\f' or '\r'][+ or -][zero more than 0-9][.][zero more than 0-9][e or E[+ or -]zero more than 0-9]. Internal of [] is optional.

If the convertion fails, a exception occuer.

  my $string = "1.25";
  my $num = strtod($string);

=head2 uc

  sub uc : string($str : string)

Convert a lowercase string to a uppercase string.

If the string is undef, a exception occur.

=head2 ucfirst

  sub ucfirst : string($str : string)

Convert the first character of a string to a uppercase character.

If the string is undef, a exception occur.

=head2 rindex

  sub rindex : int ($str : string, $substr : string, $offset : int)

Same as "index" function except that the search is the last of the string.

=head2 contains

  sub contains : int ($str : string, $substr : string)

If the string contains the sub string, return 1. If not, return 0.

