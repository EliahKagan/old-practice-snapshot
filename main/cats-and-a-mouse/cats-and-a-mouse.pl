#!/usr/bin/env perl

use strict;
use warnings;

for (1..<>) {
    my ($cat_a, $cat_b, $mouse_c) = split / /ms, <>;

    my $ac = abs $cat_a - $mouse_c;
    my $bc = abs $cat_b - $mouse_c;

    if ($ac < $bc) {
        print "Cat A\n";
    } elsif ($ac > $bc) {
        print "Cat B\n";
    } else {
        print "Mouse C\n";
    }
}
