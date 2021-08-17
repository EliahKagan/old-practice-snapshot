#!/usr/bin/env perl

use strict;
use warnings;

sub bail {
    my($fmt, @args) = @_;
    die $0, ': ',  sprintf($fmt, @args), "\n";
}

@ARGV == 2 or bail 'too %s arguments', (@ARGV < 2 ? 'few' : 'many');
open FIRST, '<', $ARGV[0] or bail "can't open the first file";
open SECOND, '<', $ARGV[1] or bail "can't open the second file";

while (defined(my $first = <FIRST>) | defined(my $second = <SECOND>)) {
    print $first if defined($first);
    print $second if defined($second);
}

close SECOND;
close FIRST;
