#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
use List::Util qw(min);

# Reads a line of text, stripping whitespace.
sub read_text {
    my $line = <>;
    $line =~ s/^\s+//msx;
    $line =~ s/\s+$//msx;
    return $line;
}

# Wagner-Fishcer algorithm
sub distance {
    my ($s, $t) = @_;
    if (length $s < length $t) { ($s, $t) = ($t, $s); }

    my $pre = [(undef) x (length($t) + 1)];
    my $cur = [0..length $t];

    for my $i (1..length $s) {
        ($pre, $cur) = ($cur, $pre);
        $cur->[0] = $i;

        for my $j (1..length $t) {
            if (substr($s, $i - 1, 1) eq substr($t, $j - 1, 1)) {
                $cur->[$j] = $pre->[$j - 1];
            } else {
                $cur->[$j] = 1 + min($cur->[$j - 1],
                                     $pre->[$j],
                                     $pre->[$j - 1]);
            }
        }
    }

    return $cur->[-1];
}

for (1..<>) {
    say distance(read_text(), read_text());
}
