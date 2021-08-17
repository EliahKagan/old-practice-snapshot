awk '{ printf "%s%s", $0, (FNR % 2 == 0 ? "\n" : ";") }'
