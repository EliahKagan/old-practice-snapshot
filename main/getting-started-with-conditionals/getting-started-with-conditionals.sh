read -r
if [[ $REPLY =~ ^[Yy]$ ]]; then
    echo YES
elif [[ $REPLY =~ ^[Nn]$ ]]; then
    echo NO
fi
