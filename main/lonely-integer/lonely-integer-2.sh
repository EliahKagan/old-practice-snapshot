declare -i n=0
read -r n

declare -ai a=()
read -ra a

printf '%d\n' ${a[*]:0:$n} | sort -n | uniq -u
