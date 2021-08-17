mapfile -t
printf '%s\n' "${MAPFILE[*]/[[:upper:]]/.}"
