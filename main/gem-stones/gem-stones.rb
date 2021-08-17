require 'set'
n = gets.to_i
alph = Set.new ?a..?z
set = (1..n).reduce(alph) {|acc, unused| acc & Set.new(gets.chomp.split '')}
puts set.size
