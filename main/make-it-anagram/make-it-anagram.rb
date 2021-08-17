h = Hash.new 0
a, b = gets.chomp, gets.chomp

0.upto(a.size - 1) {|i| h[a[i]] += 1}
0.upto(b.size - 1) {|i| h[b[i]] -= 1}

puts h.values.map(&:abs).reduce(0, :+)
