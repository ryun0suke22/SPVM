package SPVM::Math;

use SPVM 'Math';

1;

=head1 NAME

SPVM::Math - Math Library

=head1 FUNCTIONS

=head2 E

B<double E()>

The double value that is closer than any other to e, the base of the natural logarithms.

=head2 PI

B<double PI()>

The double value that is closer than any other to pi, the ratio of the circumference of a circle to its diameter.

=head2 sin

B<double sin(double $x)>

Returns the trigonometric sine of an angle. Special cases:

=over 2

=item* If the argument is NaN or an infinity, then the result is NaN.

=item* If the argument is zero, then the result is a zero with the same sign as the argument.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - an angle, in radians.

B<Returns:>

the sine of the argument.

=head2 cos

B<double cos(double $x)>

Returns the trigonometric cosine of an angle. Special cases:

=over 2

=item* If the argument is NaN or an infinity, then the result is NaN.

=back

The computed result must be within 1 ulp of the exact result. Results must be semi-monotonic.

B<Parameters:>

$x - an angle, in radians.

B<Returns:>

the cosine of the argument.
