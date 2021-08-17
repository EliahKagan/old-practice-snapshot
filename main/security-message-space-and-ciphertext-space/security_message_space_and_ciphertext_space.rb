puts gets.chomp.split('').map(&:to_i).map { |i| (i + 1) % 10 }.join('')
