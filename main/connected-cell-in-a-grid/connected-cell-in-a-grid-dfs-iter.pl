#!/usr/bin/env perl

use strict;
use warnings;
use v5.20;
use experimental qw(lexical_subs signatures);
use List::Util qw(max);

sub read_grid() {
    my $height = <<>>;
    my $width = <<>>;
    my @grid = map { [split /\s+/, <<>>] } (1..$height);
    $height, $width, \@grid;
}

sub max_component_size($height, $width, $grid) {
    my sub on_grid($i, $j) {
        0 <= $i && $i < $height && 0 <= $j && $j < $width;
    }

    my @stack;

    my sub dfs($i, $j) {
        $grid->[$i][$j] or return 0;
        $grid->[$i][$j] = 0;
        push @stack, [$i, $j];
        my $acc = 1;

        while (@stack) {
            ($i, $j) = @{pop @stack};

            for my $h ($i - 1 .. $i + 1) {
                for my $k ($j - 1 .. $j + 1) {
                    on_grid($h, $k) && $grid->[$h][$k] or next;
                    $grid->[$h][$k] = 0;
                    push @stack, [$h, $k];
                    ++$acc;
                }
            }
        }

        $acc;
    }

    my $res = 0;
    for my $i (0..$height) {
        for my $j (0..$width) {
            $res = max($res, dfs($i, $j));
        }
    }

    $res;
}

my ($height, $width, $grid) = read_grid();
say max_component_size($height, $width, $grid);
