h = Hash.new 0
a = gets.chomp
b = gets.chomp

(0...a.size).each { |i| h[a[i]] += 1 }
(0...b.size).each { |i| h[b[i]] -= 1 }

puts h.values.map(&:abs).reduce(0, :+)
