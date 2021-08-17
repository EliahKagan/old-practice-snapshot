#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);
use Const::Fast;
use Data::Dumper;
use List::Util qw(all max);

const my $NMAX => 1000;
const my $MOD => 10**9 + 7;

const my $RIGHT_ONLY => 1;
const my $DOWN_ONLY => 2;
const my $RIGHT_OR_DOWN => 3;

const my $CHECK_RANGE => 1;
const my $DEBUG_TABULATION => 0; # prints tables at the end, to standard error

sub create_uniform_grid {
    my ($size, $element) = @_;
    return map { [($element) x $size] } (1..$size);
}

sub read_problem { # Reads and returns the size and contents of the maze.
    my $n = <>;
    (0 < $n && $n <= $NMAX) or croak 'wrong maze size';

    my @maze = map { [split q{ }, <>] } (1..$n);
    all { @{$_} == $n } @maze or croak 'wrong maze shape';

    if ($CHECK_RANGE) {
        all { all { $RIGHT_ONLY <= $_ && $_ <= $RIGHT_OR_DOWN } @{$_} } @maze
            or croak 'bad value in grid';
    }

    return $n, @maze;
}

for (1..<>) {
    my ($n, @maze) = read_problem();

    # Create matrices to store each cell's adventure and path count.
    # Path counts aren't reliabile for reachability because they can hit $MOD
    # and wrap to 0, but a cell is reachable iff it has nonzero adventure.
    my @adventure = create_uniform_grid($n, 0);
    $adventure[0]->[0] = $maze[0]->[0];
    my @paths = create_uniform_grid($n, 0);
    $paths[0]->[0] = 1;

    # Compute "adventure" values and path counts for the top row.
    for my $j (1  .. $n - 1) {
        if ($maze[0]->[$j - 1] == $DOWN_ONLY) { last }
        $adventure[0]->[$j] = $maze[0]->[$j] + $adventure[0]->[$j - 1];
        $paths[0]->[$j] = 1;
    }

    # Compute "adventure" values and path counts for the rest of the maze.
    for my $i (1 .. $n - 1) {
        if ($maze[$i - 1]->[0] == $RIGHT_ONLY) { last }
        $adventure[$i]->[0] = $maze[$i]->[0] + $adventure[$i - 1]->[0];
        $paths[$i]->[0] = 1;
    }

    # Compute "adventure" values and path counts for the rest of the maze.
    for my $i (1 .. $n - 1) {
        for my $j (1 .. $n - 1) {
            my $fell = $adventure[$i - 1]->[$j] != 0
                         && $maze[$i - 1]->[$j] != $RIGHT_ONLY;
            my $slid = $adventure[$i]->[$j - 1] != 0
                         && $maze[$i]->[$j - 1] != $DOWN_ONLY;

            if (!($fell || $slid)) { next }

            if ($fell) {
                $adventure[$i]->[$j] = max($adventure[$i]->[$j],
                                           $adventure[$i - 1]->[$j]);
                $paths[$i]->[$j] += $paths[$i - 1]->[$j];
            }

            if ($slid) {
                $adventure[$i]->[$j] = max($adventure[$i]->[$j],
                                           $adventure[$i]->[$j - 1]);
                $paths[$i]->[$j] += $paths[$i]->[$j - 1];
            }

            $adventure[$i]->[$j] += $maze[$i]->[$j];
            $paths[$i]->[$j] %= $MOD;
        }
    }

    print "$paths[-1]->[-1] $adventure[-1]->[-1]\n";

    if ($DEBUG_TABULATION) {
        print {*STDERR} "\nPATHS:\n", Dumper(\@paths),
                        "\nADVENTURE:\n", Dumper(\@adventure);
    }
}
