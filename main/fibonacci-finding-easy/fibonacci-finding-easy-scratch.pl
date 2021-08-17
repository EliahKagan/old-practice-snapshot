#!/usr/bin/env perl

use strict;
use warnings;

use constant MOD => 10**9 + 7;

sub mul {
    my ($ma, $mb) = (@_);

    return [[($ma->[0]->[0] * $mb->[0]->[0]
                + $ma->[0]->[1] * $mb->[1]->[0]) % MOD,
             ($ma->[0]->[0] * $mb->[0]->[1]
                + $ma->[0]->[1] * $mb->[1]->[1]) % MOD],
            [($ma->[1]->[0] * $mb->[0]->[0]
                + $ma->[1]->[1] * $mb->[1]->[0]) % MOD,
             ($ma->[1]->[0] * $mb->[0]->[1]
                + $ma->[1]->[1] * $mb->[1]->[1]) % MOD]];
}

my $result = mul [[1, 2], [3, 4]], [[5, 6], [7, 8]];
local $" =  "\t";
print "@{$result->[0]}\n@{$result->[1]}\n";
