#!/usr/bin/perl

use strict;
use warnings;
use 5.010;

sub mean {
    my $acc = 0;
    $acc += $_ for @_;
    $acc / @_
}

sub above_average {
    my $avg = mean @_;
    my @ret;
    for (@_) { push @ret, $_ if $avg < $_ };
    @ret;
}

my @res = above_average(@ARGV);
say "@res";
