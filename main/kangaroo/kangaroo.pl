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

    if ($x1 == $x2) { return 1 } # their starting positions are the same

    my $dx = $x2 - $x1;
    my $dv = $v2 - $v1;

    return $dv != 0                     # the distance betwween them changes
            && $dx % $dv == 0           # their meeting point is on a gridline
            && !same_sign($dx, $dv);    # their meeting point is in the future
}

my $message = (will_meet(split / /, <>) ? 'YES' : 'NO');
print "$message\n";
