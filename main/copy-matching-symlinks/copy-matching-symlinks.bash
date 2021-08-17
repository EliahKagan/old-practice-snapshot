#!/bin/bash

shopt -s globstar dotglob nocaseglob

for f in **/*.cr2; do
    mkdir -p "$1/$(dirname "$f")"
    ln -s "$PWD/$f" "$1/$f"
done