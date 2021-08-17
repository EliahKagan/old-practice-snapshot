#!/usr/bin/env perl
# x1 + v1 t = x2 + v2 t, so t = (x2 - x1) / (v1 - v2). t may be undefined.
# We need x1 = x2 or for t to be a positive integer.

use strict;
use warnings;

sub same_sign {
    my ($p, $q) = @_;
    return ($p <=> 0) == ($q <=> 0);
}

sub will_meet {
    my ($x1, $v1, $x2, $v2) = @_;

    my $dx = $x2 - $x1;
    if ($x1 == $x2) { return 1 } # already together

    my $neg_dv = $v1 - $v2;

    return $neg_dv != 0                 # the gap between them is changing
            && same_sign($dx, $neg_dv)  # the gap is narrowing, not widening
            && $dx % $neg_dv == 0;      # they meet at a tick (both on ground)
}

my $message = (will_meet(split / /, <>) ? 'YES' : 'NO');
print "$message\n";
