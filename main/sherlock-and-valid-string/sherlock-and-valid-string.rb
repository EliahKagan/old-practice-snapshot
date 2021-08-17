def valid? s
	# letter in s -> how many times it appears in s
	charfreqs = Hash.new 0
	0.upto(s.size - 1) {|i| charfreqs[s[i]] += 1}

	# number of times -> number of distinct letters appearing that often
	freqfreqs = Hash.new 0
	charfreqs.values.each {|freq| freqfreqs[freq] += 1}

	# 0 or 1 frequencies: valid; more than 2 frequencies: invalid
	return freqfreqs.count < 2 unless freqfreqs.count == 2

	# if we just have to remove 1 occurrence of 1 letter: valid
	return true if freqfreqs[1] == 1

	# if one letter appears one time more often than each other letter,
	# then a single occurrence of that more frequent letter may be removed
	# so all letters appear equally frequently -- such a string is valid
	lowfreq, highfreq = freqfreqs.keys.min, freqfreqs.keys.max
	return highfreq - lowfreq == 1 && freqfreqs[highfreq] == 1
end

puts valid?(gets.chomp) ? 'YES' : 'NO'
