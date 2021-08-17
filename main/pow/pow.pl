#!/usr/bin/env perl

use strict;
use warnings;
use Math::BigInt;

# This is a demonstration. There is no actual need to implement exponentation
# for BigInt, because ** supports it. This technique is often useful, though,
# as it works for implementing exponentiation one one's own data types. For
# example, this algorithm is commonly used to implement the operation of
# raising a square matrix to a power, when one has implemented matrix
# multiplication.
sub pow {
    my ($base, $expt) = @_;
    $expt >= 0 or die "negative exponents are not supported\n";
    $expt == int $expt or die "fractional exponent are not supported\n";

    return Math::BigInt->bone() if $expt == 0; # the empty product is 1

    my $result = pow($base, int $expt / 2);
    $result *= $result;
    if ($expt % 2 != 0) { $result *= $base }
    return $result;
}

@ARGV == 2 or die "need exactly two arguments, a base and exponent\n";
my $base = Math::BigInt->new(shift @ARGV);
my $exponent = shift @ARGV;
print pow($base, $exponent), "\n";
