mapfile -t
declare -a a=(${MAPFILE[@]} ${MAPFILE[@]} ${MAPFILE[@]})
printf '%s\n' "${a[*]}"
