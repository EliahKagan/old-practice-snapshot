def getRecord
	gets.split.map &:to_i
end

gets.to_i.times do
	n, k = getRecord
	puts getRecord.take(n).reject{|time| time > 0}.size < k ? 'YES' : 'NO'
end
