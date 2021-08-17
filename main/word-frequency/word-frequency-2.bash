#!/bin/bash
<words.txt xargs printf '%s\n' | sort | uniq -c | sort -rn | awk '{ print $2, $1 }'
