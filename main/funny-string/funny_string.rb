gets.to_i.times do
  s = gets.chomp.split('').map(&:ord)
  r = s.reverse
  n = s.size

  funny = (1...n).all? { |i| (s[i] - s[i - 1]).abs == (r[i] - r[i - 1]).abs }
  puts funny ? 'Funny' : 'Not Funny'
end
