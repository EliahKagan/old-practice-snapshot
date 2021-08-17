#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;

use Carp qw(croak);
use English qw(-no_match_vars);
use Getopt::Long qw(GetOptions :config gnu_getopt no_auto_abbrev);
use List::Util qw(all);

use constant {
    FUSE_TIME => 3,
    NORMAL_RULES_START => 2,
    PLANTING_PERIOD => 2
};

use constant {
    EMPTY_SYMBOL => q{.},
    BOMB_SYMBOL => q{O}
};

my $verbose = 0;
GetOptions('verbose|v' => \$verbose);
my $info; # will have separate implementations based on verbosity

if ($verbose) {
    $info = sub {
        my @args = @_;
        say {*STDERR} "$PROGRAM_NAME: ", @args;
    };
} else {
    $info = sub { };
}

sub trim {
    my ($text) = @_;
    $text =~ s/\A\s+//msx;
    $text =~ s/\s+\z//msx;
    return $text;
}

sub read_row {
    my $line = <>;
    my @chars = split //msx, trim($line);
    return map { $_ eq BOMB_SYMBOL ? FUSE_TIME : 0 } @chars;
}

sub read_grid {
    my ($r, $c) = @_;
    my @grid = map { [read_row] } (1..$r);
    all { scalar @{$_} == $c } @grid or croak 'wrong shape while reading grid';
    return @grid;
}

sub write_grid {
    my @grid = @_;
    for my $row (@grid) {
        say map { $_ == 0 ? EMPTY_SYMBOL : BOMB_SYMBOL } @{$row};
    }
    return;
}

my ($r, $c, $n) = split /\s+/msx, <>;
my @grid = read_grid $r, $c;

my $imax = $r - 1;
my $jmax = $c - 1;

sub flatten {  # helper subroutine for serialize()
    return map { @{$_} } @grid;
}

sub serialize {
    return join q{}, flatten;
}

sub unflatten {  # helper subroutine for deserialize()
    my ($state) = @_;

    length $state == $r * $c
        or croak 'Internal error: wrong shape while deserializing state';

    return split /.{$c}\K/msx, $state;
}

sub deserialize {
    my ($state) = @_;
    return map { [split //msx] } unflatten $state;
}

sub in_blast {
    my ($i, $j) = @_;

    return ($i != 0 && $grid[$i - 1]->[$j] == 1)
        || ($i != $imax && $grid[$i + 1]->[$j] == 1)
        || ($j != 0 && $grid[$i]->[$j - 1] == 1)
        || ($j != $jmax && $grid[$i]->[$j + 1] == 1);
}

sub clear_blast_zones { # removes non-bombs that are about to be destroyed
    for my $i (0..$imax) {
        for my $j (0..$jmax) {
            if ($grid[$i]->[$j] > 1 && in_blast($i, $j)) {
                $grid[$i]->[$j] = 0;
            }
        }
    }
    return;
}

sub count_down { # reduces bomb timers by one tick, removing detonated bombs
    for my $row (@grid) {
        for my $elem (@{$row}) {
            if ($elem != 0) { --$elem }
        }
    }
    return;
}

sub burn_fuses {
    clear_blast_zones;
    count_down;
    return;
}

sub plant_bombs { # plants bombs on empty squares 
    for my $row (@grid) {
        for my $elem (@{$row}) {
            if ($elem == 0) { $elem = FUSE_TIME }
        }
    }
    return;
}

my @states; # time => state (from beginning)
my %times;  # state => time (after initial steps)

sub write_history { # always maps time to state; maps state to time if told to
    my $time = shift;
    my $map_to_time = shift // 1; # assume we _do_ want to map state to time

    my $state = serialize;
    scalar @states == $time
        or croak q{Internal error: some previous state wasn't recorded};
    push @states, $state;

    if ($map_to_time) {
        my $old_time = $times{$state};
        if (defined $old_time) { return $old_time }
        $times{$state} = $time;
    }

    return;
}

sub pre_run { # we must manually enter the first two ticks, as they are special
      write_history 0, 0;
      burn_fuses;
      write_history 1, 0;
      return;
}

sub run { # automatically simulate other ticks; return the earliest end time
    for my $time (NORMAL_RULES_START..$n) {
        burn_fuses;
        if ($time % PLANTING_PERIOD == 0) { plant_bombs }

        my $old_time = write_history $time;
        if (defined $old_time) {
            NORMAL_RULES_START <= $old_time
                or croak 'Internal error: '
                        . q{states weren't periodic yet at $old_time};

            my $state_period = $time - $old_time;
            $state_period > 0
                or croak 'Internal error: nonpositive $state_period';

            my $end_time = $old_time + ($n - $old_time) % $state_period;
            ($old_time <= $end_time && $end_time < $time)
                or croak 'Internal error: $end_time is out of range';

            return $end_time;
        }
    }

    return $n;
}

pre_run;
my $end_time = run;
$info->("\$end_time: $end_time");

write_grid deserialize($states[$end_time]);
