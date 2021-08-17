#!/usr/bin/env perl

use strict;
use warnings;

use English;
use Term::ANSIColor;

my $pattern = shift @ARGV
    or die "Usage: $PROGRAM_NAME PATTERN [FILE]...\n";

while (<>) {
    if (/$pattern/) {
        printf "%s%s%s\n",
               $PREMATCH, colored($MATCH, 'bright_red'), $POSTMATCH;
    }
}
