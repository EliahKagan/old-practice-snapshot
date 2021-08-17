read -r; grep -oP '<\s*\K[[:alpha:]][[:alnum:]]*\b' | sort -u | paste -sd \; -
