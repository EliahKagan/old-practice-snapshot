h = Hash.new 0
s = gets.chomp
0.upto(s.size - 1) {|i| h[s[i]] += 1}
puts h.values.reduce(0) {|acc, v| acc + v % 2} > 1 ? 'NO' : 'YES'
