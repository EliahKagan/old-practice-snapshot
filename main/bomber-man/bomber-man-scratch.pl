#!/usr/bin/env perl

use strict;
use warnings;
use feature qw(say);
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

if ($verbose) {
    my $log = sub {
        my @args = @_;
        print {*STDERR} "$PROGRAM_NAME: ", @args;
    };
} else {
    my $log = sub { };
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
}

# FIXME: implement serialize() and deserialize() here

my ($r, $c, $n) = split /\s+/msx, <>;
my @grid = read_grid $r, $c;

# FIXME: remove these statements after testing
say "r=$r, c=$c, n=$n";
say scalar @grid;
write_grid @grid;
