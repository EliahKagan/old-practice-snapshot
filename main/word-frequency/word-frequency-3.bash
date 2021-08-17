#!/bin/bash

<words.txt awk '
    { for (i = 1; i <= NF; ++i) ++freq[$i] }
    END { for (word in freq) print word, freq[word] }' | sort -nrk2
