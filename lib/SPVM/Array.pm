package SPVM::Array;

1;

=encoding utf8

=head1 Name

SPVM::Array - Array Utilities

=head1 Usage

  use Array;
  
  # Copy a byte array
  {
    my $array = [(byte)1, 2, 3];
    my $array_copy = Array->copy_byte($array);
  }

  # Copy a short array
  {
    my $array = [(short)1, 2, 3];
    my $array_copy = Array->copy_short($array);
  }

  # Copy a int array
  {
    my $array = [1, 2, 3];
    my $array_copy = Array->copy_int($array);
  }

  # Copy a long array
  {
    my $array = [(long)1, 2, 3];
    my $array_copy = Array->copy_long($array);
  }

  # Copy a float array
  {
    my $array = [1.5f, 2.5f, 3.5f];
    my $array_copy = Array->copy_float($array);
  }

  # Copy a double array
  {
    my $array = [1.5, 2.5, 3.5];
    my $array_copy = Array->copy_double($array);
  }
  
  # Copy a string array
  {
    my $array = ["abc", "def", "ghi"]
    my $array_copy = Array->copy_string($array);
  }
  
  # Check if the two byte arrays equal
  {
    my $array1 = [(byte)1, 2];
    my $array2 = [(byte)1, 2];
    my $ret = Array->equals_byte($array1, $array2);
  }

  # Check if the two short arrays equal
  {
    my $array1 = [(short)1, 2];
    my $array2 = [(short)1, 2];
    my $ret = Array->equals_short($array1, $array2);
  }

  # Check if the two int arrays equal
  {
    my $array1 = [(int)1, 2];
    my $array2 = [(int)1, 2];
    my $ret = Array->equals_int($array1, $array2);
  }

  # Check if the two long arrays equal
  {
    my $array1 = [(long)1, 2];
    my $array2 = [(long)1, 2];
    my $ret = Array->equals_long($array1, $array2);
  }

  # Check if the two float arrays equal
  {
    my $array1 = [(float)1, 2];
    my $array2 = [(float)1, 2];
    my $ret = Array->equals_float($array1, $array2);
  }

  # Check if the two double arrays equal
  {
    my $array1 = [(double)1, 2];
    my $array2 = [(double)1, 2];
    my $ret = Array->equals_double($array1, $array2);
  }

  # Check if the two string arrays equal
  {
    my $array1 = ["abc", "def"];
    my $array2 = ["abc", "def"];
    my $ret = Array->equals_string($array1, $array2);
  }
  
  # Copy object array
  my $array = [(object)Int->new(1), Int->new(2), Int->new(3)];
  my $array_copy = Array->copy_object($array, method : object ($obj : object) {
    my $int_obj = (Int)$obj;
    my $new_int_obj = Int->new($int_obj->value);
    return $new_int_obj;
  });

=head1 Description

C<Array> provides array utilities.

=head1 Class Methods

=head2 copy_byte

  static method copy_byte : byte[] ($array : byte[])

Copy a byte array.

If the array is undef, return undef.

=head2 copy_double

  static method copy_double : double[] ($array : double[])

Copy a double array.

If the array is undef, return undef.

=head2 copy_float

  static method copy_float : float[] ($array : float[])

Copy a float array.

If the array is undef, return undef.

=head2 copy_int

  static method copy_int : int[] ($array : int[])

Copy a int array.

If the array is undef, return undef.
  
=head2 copy_long

  static method copy_long : long[] ($array : long[])

Copy a long array.

If the array is undef, return undef.

=head2 copy_object

  static method copy_object : object[] ($array : object[], $cloner : Cloner)

Copy a object array with a L<Cloner|SPVM::Cloner> callback implemetation.

If the array is undef, return undef.

=head2 copy_range_byte

  static method copy_range_byte : byte[] ($array : byte[], $offset : int, $length : int)
  
Slice array in the byte array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_double

  static method copy_range_double : double[] ($array : double[], $offset : int, $length : int)

Slice array in the double array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_float

  static method copy_range_float : float[] ($array : float[], $offset : int, $length : int)

Slice array in the float array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_int

  static method copy_range_int : int[] ($array : int[], $offset : int, $length : int)

Slice array in the int array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_long

  static method copy_range_long : long[] ($array : long[], $offset : int, $length : int)

Slice array in the long array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_object

  static method copy_range_object : object[] ($array : object[], $offset : int, $length : int)

Slice array in the object array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_short

  static method copy_range_short : short[] ($array : short[], $offset : int, $length : int)

Slice array in the short array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_range_string
  
  static method copy_range_string : string[] ($array : string[], $offset : int, $length : int)

Slice array in the string array with the start offset and the length.

Array must be defined, otherwise an exception occurs.

Offset must be in the array range, otherwise an exception occurs.

Length must be more than or equals to 0, othrewise an exception occurs.

Offset + length must not be in the array range, othrewise an exception occurs.

=head2 copy_short

  static method copy_short : short[] ($array : short[])

Copy a short array.

If the array is undef, return undef.
  
=head2 copy_string

  static method copy_string : string[] ($array : string[])

Copy a string array.

If the array is undef, return undef.

=head2 dump_byte

  static method dump_byte : string ($array : byte[])
  
Convert the array in the byte array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_double

  static method dump_double : string ($array : double[])
  
Convert the array in the double array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_float

  static method dump_float : string ($array : float[])
  
Convert the array in the float array to string and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_int

  static method dump_int : string ($array : int[])
  
Convert the array in the int array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_long

  static method dump_long : string ($array : long[])
  
Convert the array in the long array to string and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_object

  static method dump_object : string ($array : object[], $stringer : Stringer)
  
Convert the array in the object array to string by a C<SPVM::Stringer> callback implementation and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_short

  static method dump_short : string ($array : short[])
  
Convert the array in the short array to string and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_string

  static method dump_string : string ($array : string[])
  
Join the array in the array with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If string array is undef, return undef.

=head2 dump_unsigned_byte

  static method dump_unsigned_byte : string ($array : byte[])
  
Convert the array in the byte array to string interpreting as an unsigned 8bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_unsigned_int

  static method dump_unsigned_int : string ($array : int[])
  
Convert the array in the int array to string interpreting as an unsigned 32bit integer and join them with "," and surround it with "[" and "]", and return it.

If byte array is undef, return undef.

=head2 dump_unsigned_long

  static method dump_unsigned_long : string ($array : long[])
  
Convert the array in the long array to string interpreting as an unsigned 64bit integer and join them with "," and surround it with "[" and "]", and return it.

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 dump_unsigned_short

  static method dump_unsigned_short : string ($array : short[])
  
Convert the array in the short array to string interpreting as an unsigned 16bit integer and join them with "," and surround it with "[" and "]".

For readability spaces and line breaks are inserted.

If byte array is undef, return undef.

=head2 equals_byte

  static method equals_byte : int ($array1 : byte[], $array2 : byte[])

Check if two byte arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_double

  static method equals_double : int ($array1 : double[], $array2 : double[])

Check if two double arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_float

  static method equals_float : int ($array1 : float[], $array2 : float[])

Check if two float arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_int

  static method equals_int : int ($array1 : int[], $array2 : int[])

Check if two int arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_long

  static method equals_long : int ($array1 : long[], $array2 : long[])

Check if two long arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_object

  static method static method equals_object : int ($objs1 : object[], $objs2 : object[], $equality_checker : EqualityChecker)

Check equality of two array. You must sepecify a L<EqualityChecker|SPVM::EqualityChecker> object to check the equality of each element.

$objs1 and $objs2 and $equality_checker must be defined, otherwise an exception occurs.

Return 1 if the length of $objs1 and $objs2 is same and all element is same, otherwise return C<0>.

=head2 equals_object_address

  static method equals_object_address : int ($array1 : object[], $array2 : object[])

The alias for the following code using L</"equals_object">.

  my $ret = &equals_object($array1, $array2, EqualityChecker::SameObject->new);

=head2 equals_short

  static method equals_short : int ($array1 : short[], $array2 : short[])

Check if two short arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 equals_string

  static method equals_string : int ($array1 : double[], $array2 : double[])

Check if two string arrays equal.

If at least one of the arrays is undef, a excetpion occurs.

=head2 memcpy_byte

  static method memcpy_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_double
  
  static method memcpy_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_float
  
  static method memcpy_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_int
  
  static method memcpy_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_long
  
  static method memcpy_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_short

  static method memcpy_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memcpy_object

  static method memcpy_object : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int)

Copy source object array to destination object array with the each offset and a length.

If source data range and destination data overlap, the result is not guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove

  static method memmove : void ($dest : object, $dest_byte_offset : int, $source : object, $source_byte_offset : int, $byte_length : int);

The destination must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

If the destination is a read-only string, an exception is thrown.

The source must be a string type, a numeric type, or a multi numeric type, otherwise an exception is thrown.

Copy the source to the destination with the given each offset and the given length by byte unit.

If source data range and destination data overlap, the result is not guaranteed.

The destnation must be defined, otherwise an exception occurs.

The source must be defined, otherwise an exception occurs.

The length must be more than or equals to 0, otherwise an exception occurs.

The destnation byte offset + byte length must be within the byte range of the destnation, otherwise an exception occurs.

The source byte offset + byte length must be within the byte range of the source, otherwise an exception occurs.

=head2 memmove_byte

  static method memmove_byte : void ($dest : byte[], $dest_offset : int, $source : byte[], $source_offset : int, $length : int)

Copy source byte array to destination byte array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_double
  
  memmove_double : void ($dest : double[], $dest_offset : int, $source : double[], $source_offset : int, $length : int)

Copy source double array to destination double array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_float
  
  static method memmove_float : void ($dest : float[], $dest_offset : int, $source : float[], $source_offset : int, $length : int)

Copy source float array to destination float array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_int
  
  memmove_int : void ($dest : int[], $dest_offset : int, $source : int[], $source_offset : int, $length : int)

Copy source int array to destination int array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_long
  
  memmove_long : void ($dest : long[], $dest_offset : int, $source : long[], $source_offset : int, $length : int)

Copy source long array to destination long array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_short

  memmove_short : void ($dest : short[], $dest_offset : int, $source : short[], $source_offset : int, $length : int)

Copy source short array to destination short array with the each offset and a length.

Even if source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memmove_object

  static method memmove_object : void ($dest : object[], $dest_offset : int, $source : object[], $source_offset : int, $length : int)

Copy source object array to destination object array with the each offset and a length.

If source data range and destination data overlap, the result is guaranteed.

Destnation must be defined, otherwise an exception occurs.

Source must be defined, otherwise an exception occurs.

Length must be more than or equals to 0, otherwise an exception occurs.

Destnation offset + length must be within the range of the destnation array, otherwise an exception occurs.

Source offset + length must be within the range of the source array, otherwise an exception occurs.

=head2 memset_byte

  static method memset_byte : void ($dest : byte[], $dest_offset : int, $element : byte, $length : int)

Set each element of the C<byte> array to the element with the offset and the length.

=head2 memset_double

  static method memset_double : void ($dest : double[], $dest_offset : int, $element : double, $length : int)

Set each element of the C<double> array to the element with the offset and the length.

=head2 memset_float

  static method memset_float : void ($dest : float[], $dest_offset : int, $element : float, $length : int)

Set each element of the C<float> array to the element with the offset and the length.

=head2 memset_int

  static method memset_int : void ($dest : int[], $dest_offset : int, $element : int, $length : int)

Set each element of the C<int> array to the element with the offset and the length.

=head2 memset_long

  static method memset_long : void ($dest : long[], $dest_offset : int, $element : long, $length : int)

Set each element of the C<long> array to the element with the offset and the length.

=head2 memset_short

  static method memset_short : void ($dest : short[], $dest_offset : int, $element : short, $length : int)

Set each element of the C<short> array to the element with the offset and the length.

=head2 memset_object

  static method memset_object : void ($dest : object[], $dest_offset : int : int, $element : object, $length)

Set each element of the object array to the element with the offset and the length.

=head2 new_proto

  static method new_proto : object[] ($proto_array : object[], $length : int)

Create a new generic object array as the same type as the given array.

