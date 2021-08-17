# determine dimensions for "ciphertext" grid
s = gets.gsub(/\s+/, '').freeze
n = s.size
sqrt = Math.sqrt(n)
h = sqrt.floor.to_int
w = sqrt.ceil.to_int
h += 1 if h * w < n

# create empty grid and populate it with ciphertext
newcol = (' ' * h).freeze
grid = (1..w).map { newcol.dup } # column-major ciphertext representation
(0...n).each { |k| grid[k % w][k / w] = s[k] }

# output ciphertext
puts grid.each(&:rstrip!).join(' ')
