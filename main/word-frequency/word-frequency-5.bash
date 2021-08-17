perl -wne 'for my $w (split q{ }) { ++$f{$w} } END { for my $w (reverse sort { $f{$a} <=> $f{$b} } keys %f) { printf "$w $f{$w}\n" } }' words.txt
