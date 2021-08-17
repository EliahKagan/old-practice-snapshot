read -r
e='\b[[:alnum:]]*[[:alpha:]](?=\s*<)'
rev | grep -oP "$e" | rev | sort -u | paste -sd \; -
