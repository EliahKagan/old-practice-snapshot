#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use List::Util qw(max min sum);

sub read_record {
    return split /\s+/msx, <>;
}

sub read_row_col { # convert from 1-based to 0-based indexing
    my ($r, $c) = read_record;
    return $r - 1, $c - 1;
}

my ($board_size, $obstacle_count) = read_record;
my ($queen_row, $queen_col) = read_row_col;
my %attack_ranges;

sub get_range {
    my ($dir_row, $dir_col) = @_;
    return $attack_ranges{"$dir_row $dir_col"};
}

sub set_range {
    my ($dir_row, $dir_col, $mag) = @_;
    $attack_ranges{"$dir_row $dir_col"} = $mag;
    # print {*STDERR} "Set dir_row=$dir_row, dir_col=$dir_col, mag=$mag.\n";
    return;
}

sub init_cardinal_ranges {
    set_range -1, 0, $queen_row + 1;            # north
    set_range 1, 0, $board_size - $queen_row;   # south
    set_range 0, -1, $queen_col + 1;            # west
    set_range 0, 1, $board_size - $queen_col;   # east
    return;
}

sub init_intercardinal_ranges {
    for my $dir_row (-1, 1) { # north-, south-
        for my $dir_col (-1, 1) { # -east, -west
            my $mag = min get_range($dir_row, 0), get_range(0, $dir_col);
            set_range $dir_row, $dir_col, $mag;
        }
    }
    return;
}

sub update_range { # helper function for add_obstacle
    my ($dir_row, $dir_col, $mag) = @_;
    my $dir = "$dir_row $dir_col";
    $attack_ranges{$dir} = min $attack_ranges{$dir}, $mag;
    return;
}

sub add_obstacle {
    my ($row, $col) = @_;
    my $delta_row = $row - $queen_row;
    my $delta_col = $col - $queen_col;

    my $mag_row = abs $delta_row;
    my $mag_col = abs $delta_col;

    if ($mag_row == 0 || $mag_col == 0 || $mag_row == $mag_col) {
        my $dir_row = $delta_row <=> 0;
        my $dir_col = $delta_col <=> 0;
        update_range $dir_row, $dir_col, max($mag_row, $mag_col);
    }

    return;
}

init_cardinal_ranges;
init_intercardinal_ranges;
for (1..$obstacle_count) { add_obstacle read_row_col }

scalar keys %attack_ranges == 8 or croak 'wrong number of directions';
print sum(map { $_ - 1 } values %attack_ranges), "\n";
