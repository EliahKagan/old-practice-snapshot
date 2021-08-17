read -r x
read -r y

if ((x == y)); then
    s='equal to'
elif ((x > y)); then
    s='greater than'
else
    s='less than'
fi

printf 'X is %s Y\n' "$s"
