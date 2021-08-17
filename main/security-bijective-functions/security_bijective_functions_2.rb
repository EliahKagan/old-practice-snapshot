n = gets.to_i
puts(gets.split.map(&:to_i).sort! == (1..n).to_a ? 'YES' : 'NO')
