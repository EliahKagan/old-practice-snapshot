n = gets.to_i

if n <= 1 # given problem constraints, this means n == 1
  puts gets.chomp
  exit
end

a = []
n.times { a.push(gets.chomp) }

range = 1..(n - 2) # range of interior indices (for non-border cells)
range.each do |i|
  range.each do |j|
    c = a[i][j]
    a[i][j] = 'X' if a[i][j - 1] < c && a[i][j + 1] < c &&
                     a[i - 1][j] < c && a[i + 1][j] < c
  end
end

a.each { |row| puts row }
