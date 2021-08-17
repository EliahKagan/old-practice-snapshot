read -r n

sum=0
for ((i = n; i > 0; --i)); do
    read -r
    ((sum += REPLY))
done

printf '%.3f\n' "$(bc -l <<<"$sum/$n")"
