#!/usr/bin/env perl

use strict;
use warnings;

sub printenv {
    my $key = shift;
    return print "$key=$ENV{$key}\n";
}

if (!@ARGV) {  # got no arguments, so print the whole environment
    for my $key (sort keys %ENV) {
        printenv $key;
    }

    exit 0;
}

my $got_key_not_found = 0;

for my $key (@ARGV) {
    if (exists $ENV{$key}) {
        printenv $key;
    } else {
        $got_key_not_found = 1;
    }
}

exit $got_key_not_found;
