#!/usr/bin/env perl

use strict;
use warnings;

while (my $pattern = <>) {
    my $text = <>;
    my $start = index $pattern, 'A';
    my $stop = index $pattern, 'B', $start;
    print substr($text, $start, $stop - $start + 1), "\n";
}
