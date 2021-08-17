gets.to_i.times do
	s = gets.chomp
	r = s.reverse

	funny = (1 .. s.size - 1).all? {|i|
		(s[i].ord - s[i - 1].ord).abs == (r[i].ord - r[i - 1].ord).abs
	}

	puts funny ? "Funny" : "Not Funny"
end
