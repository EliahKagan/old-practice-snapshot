def maxDecent n
	n.downto 0 do |fives|
		threes = n - fives
		return '5' * fives + '3' * threes if fives % 3 == 0 && threes % 5 == 0
	end

	return -1
end

gets.to_i.times {puts maxDecent gets.to_i}
