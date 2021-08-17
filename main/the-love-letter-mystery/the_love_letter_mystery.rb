gets.to_i.times do
  s = gets.chomp
  n = s.size
  puts((0...n / 2).reduce(0) { |a, e| a + (s[e].ord - s[n - e - 1].ord).abs })
end
