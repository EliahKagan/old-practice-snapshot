h = Hash.new 0
gets.chomp.split('').each { |c| h[c] += 1 }
puts h.values.select(&:odd?).size > 1 ? 'NO' : 'YES'
