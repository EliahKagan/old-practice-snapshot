#!/usr/bin/env perl

use strict;
use warnings;
use 5.010;

use English '-no_match_vars';

sub open_all {
    my @paths = @_;
    my @files;

    for my $path (@paths) {
        if (open my $file, '<', $path) {
            push @files, $file;
        } else {
            warn "$PROGRAM_NAME: can't open \"", $path, "\": $OS_ERROR\n";
        }
    }

    return @files;
}

my @files = open_all(@ARGV);

for (my $more = 1; $more; ) {
    $more = 0;

    for my $file (@files) {
        defined(my $line = <$file>) or next;

        $more = 1;
        chomp $line;
        say $line;
    }
}

#for my $file (@files) { close $file }
