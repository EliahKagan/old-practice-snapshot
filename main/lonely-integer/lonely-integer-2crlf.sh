declare -i n=0
tr -d '\r' | read -r n

declare -ai a=()
tr -d '\r' | read -ra a

printf '%d\n' ${a[*]:0:$n} | sort -n | uniq -u
