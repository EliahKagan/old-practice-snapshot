def countNeededChanges s
	n = s.size
	return -1 unless n % 2 == 0

	m = n / 2
	h = Hash.new 0

	(0 .. m - 1).each {|i| h[s[i]] += 1}
	(m .. n - 1).each {|i| h[s[i]] -= 1}

	h.values.select {|v| v > 0}.reduce(0, :+)
end

gets.to_i.times {puts countNeededChanges gets.chomp}
