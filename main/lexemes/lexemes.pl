#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;
use open qw(:std :utf8);

sub ordinals {
    my $text = shift // $_;
    my $nums = join q{ }, map { ord } split //ms, $text;
    return "($nums)";
}

while (<>) {
    chomp;
    say join q{ }, map { ordinals } split /\X\K/msx;
}
