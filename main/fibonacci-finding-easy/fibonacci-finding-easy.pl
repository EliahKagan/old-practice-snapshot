#!/usr/bin/env perl

use strict;
use warnings;

use constant MOD => 10**9 + 7;

use constant {
    IDENTITY => [[1, 0], [0, 1]],
    FIBONACCI_GENERATOR => [[1, 1], [1, 0]],
};

sub mul_vec {
    my ($ma, $v) = @_;

    return [($ma->[0]->[0] * $v->[0] + $ma->[0]->[1] * $v->[1]) % MOD,
            ($ma->[1]->[0] * $v->[0] + $ma->[1]->[1] * $v->[1]) % MOD];
}

sub mul {
    my ($ma, $mb) = @_;

    return [[($ma->[0]->[0] * $mb->[0]->[0]
                + $ma->[0]->[1] * $mb->[1]->[0]) % MOD,
             ($ma->[0]->[0] * $mb->[0]->[1]
                + $ma->[0]->[1] * $mb->[1]->[1]) % MOD],
            [($ma->[1]->[0] * $mb->[0]->[0]
                + $ma->[1]->[1] * $mb->[1]->[0]) % MOD,
             ($ma->[1]->[0] * $mb->[0]->[1]
                + $ma->[1]->[1] * $mb->[1]->[1]) % MOD]];
}

sub pow {
    my ($base, $expt) =  @_;

    if ($expt == 0) { return IDENTITY }

    my $factor = pow($base, int $expt / 2);
    $factor = mul($factor, $factor);
    if ($expt % 2 != 0) { $factor = mul($factor, $base) }
    return $factor;
}

sub fib {
    my ($fst, $snd, $n) = @_;
    return mul_vec(pow(FIBONACCI_GENERATOR, $n - 1), [$snd, $fst])->[0];
}

for (1..<>) {
     my ($fst, $snd, $n) = split q{ }, <>;
     print fib($fst, $snd, $n), "\n";
}
