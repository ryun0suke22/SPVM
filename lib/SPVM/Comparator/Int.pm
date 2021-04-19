package SPVM::Comparator::Int;

1;

=head1 NAME

SPVM::Comparator::Int - a callback type for int comparation

=head1 SYNOPSYS
  
  use SPVM::Comparator::Int;
  
  my $comparator : SPVM::Comparator::Int = sub : int ($self : self, $a : int, $b : int); {
    return $a <=> $b;
  };
  
  my $result = $comparator->(3, 5);

=head1 DESCRIPTION

L<SPVM::Comparator> is a callback type to compare two numbers.

=head1 CALLBACK METHOD

  sub : int ($self : self, $a : int, $b : int);

This method should receive two numbers and return 1 if $a is more than $b, -1 if $x is lass than $b, 0 if $a equals $b in the implementation.

