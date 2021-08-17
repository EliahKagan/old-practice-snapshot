s=; read -r s
declare -i n=${s%%$'\r'}

declare -ai a=()
read -ra a

printf '%d\n' ${a[*]:0:$n} | sort -n | uniq -u
