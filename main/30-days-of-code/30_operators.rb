price, tip, tax = (1..3).map { gets.to_f }

printf "The total meal cost is %.0f dollars.\n",
       price * (1.0 + (tip + tax) / 100.0)
