#!/usr/bin/env bash

# This is a very rough heuristic. For example, I often write a .java file
# without imports (or they're not from a package that starts "java") that
# doesn't comtain my entry point class. And a C translation unit may forward-
# declare all the external symbols it uses and thus require no #include
# directive. (And of course this doesn't handle quoting, odd formatting, and
# many other quite common constructs.) Please don't really use this code!

declare -r ca='^[[:space:]]*#include[[:space:]]*' \
    cb='(<[^[:space:]]+\.h>|"[^[:space:]]+\.h")[[:space:]]*$'
declare -r c="${ca}${cb}"

declare -r java1a='^[[:space:]]*import[[:space:]]+' \
    java1b='java[[:alnum:]_]?(\.([[:alnum:]_]+|\*))*[[:space:]]*;[[:space:]]*$'
declare -r java1="${java1a}${java1b}"

declare -r java2a='^[[:space:]]*public[[:space:]]+static[[:space:]]+void' \
    java2b='[[:space:]]+main[[:space:]]*\([[:space:]]*' \
    java2c='(java[[:space:]]*\.[[:space:]]*lang[[:space:]]*\.[[:space:]]*)?' \
    java2d='String[[:space:]]*\[[[:space:]]*\][[:space:]]*' \
    java2e='[[:alpha:]_][[:alnum:]_]*\)[[:space:]]*\{?[[:space:]]*$'
declare -r java2="${java2a}${java2b}${java2c}${java2d}${java2e}"

declare lang=
while [ -z "$lang" ] && read -r; do
    if [[ $REPLY =~ $c ]]; then
        lang=C
    elif [[ $REPLY =~ $java1 ]] || [[ $REPLY =~ $java2 ]]; then
        lang=Java
    fi
done

echo ${lang:-Python}
