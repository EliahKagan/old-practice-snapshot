#!/usr/bin/env perl

use strict;
use warnings;
use Carp qw(croak);

sub read_row {
    my ($width) = @_;

    my $line = <>;
    length $line == ($line =~ /\n\z/msx ? $width + 1 : $width)
        or croak 'wrong length line in text/pattern';
    return $line;
}

sub read_grid {
    my ($height, $width) = split q{ }, <>;
    my @lines = map { read_row($width) } (1..$height);
    return ($height, $width, @lines);
}

sub run {
    my ($text_height, $text_width, @text_lines) = read_grid();
    my ($pattern_height, $pattern_width, @pattern_lines) = read_grid();

    my $gap = $text_width - $pattern_width + 1; # add 1 for the newline
    if ($gap < 1) { return 0 }

    chomp @pattern_lines;
    my $pattern = join ".{$gap}", @pattern_lines;

    my $text = join q{}, @text_lines;
    return $text =~ /$pattern/msx;
}

for (1..<>) { print run() ? "YES\n" : "NO\n" }
