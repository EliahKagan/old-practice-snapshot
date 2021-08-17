h = Hash.new 0
gets.chomp.split('').each { |c| h[c] += 1 }
gets.chomp.split('').each { |c| h[c] -= 1 }
puts h.values.map(&:abs).reduce(0, :+)
