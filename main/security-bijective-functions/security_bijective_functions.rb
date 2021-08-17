n = gets.to_i
a = gets.split.map(&:to_i).sort!.uniq
puts(a.size == n && a.first == 1 && a.last == n ? 'YES' : 'NO')
