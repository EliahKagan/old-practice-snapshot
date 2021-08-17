#!/usr/bin/env bash

before='\bhttps?(:|%3A)(/|%2F){2}(ww[w\d]\.)?\K'
domain='(?!www[w\d]\.)[\w-]+(\.[\w-]+)+(?![\w-.])'
grep -ioP "${before}${domain}" | LC_COLLATE=C sort -u | paste -sd \; -
