#!/usr/bin/env bash

declare -i n=0
declare -ai a=()

read -r n
read -ra a

expr $(echo 0; printf ' + %d' ${a[*]:0:$n})
