#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(current_sub lexical_subs);
use experimental qw(signatures);
use List::Util qw(max min sum);

sub read_graph($vertex_count, $edge_count) {
    my @adj = map { [] } (0..$vertex_count); # one extra for 1-based indexing

    for (1..$edge_count) {
        my ($u, $v) = split /\s+/, <<>>;
        push @{$adj[$u]}, $v;
        push @{$adj[$v]}, $u;
    }

    \@adj;
}

sub each_nonsingleton_component_size($adj, $code) {
    my @vis = (0) x scalar @{$adj};
    my @stack;

    my sub dfs($start) {
        return 0 if $vis[$start];
        $vis[$start] = 1;
        push @stack, $start;
        my $acc = 1;

        while (@stack) {
            for my $dest (@{$adj->[pop @stack]}) {
                next if $vis[$dest];
                $vis[$dest] = 1;
                push @stack, $dest;
                ++$acc;
            }
        }

        $acc;
    }

    for my $start (1..$#{$adj}) {
        my $size = dfs($start);
        if ($size > 1) { $code->($size) };
    }

    1;
}

sub run() {
    my $n = <<>>;
    my $adj = read_graph($n * 2, $n);

    my $min = '+inf';
    my $max = '-inf';

    each_nonsingleton_component_size($adj, sub($size) {
        $min = min($min, $size);
        $max = max($max, $size);
    });

    print "$min $max\n";
}

run();
