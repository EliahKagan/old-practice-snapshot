gets.to_i.times do
	s = gets.chomp
	n = s.size
	puts (1 .. n / 2).reduce(0) {|acc, i| acc + (s[i - 1].ord - s[n - i].ord).abs}
end
