read -r x
read -r y
read -r z

if ((x == y && y == z)); then
    echo EQUILATERAL
elif ((x == y || y == z || z == x)); then
    echo ISOSCELES
else
    echo SCALENE
fi
