#!/bin/bash

perl -e '
    use strict;
    use warnings;

    my $top = <>;
    defined $top or exit;
    my @rows = map { [$_] } split q{ }, $top;

    while (<>) {
        my @col = split q{ };
        for my $i (0..$#col) { push @{$rows[$i]}, $col[$i] }
    }

    for my $row (@rows) { print join(q{ }, @{$row}), "\n" }
' file.txt
