require 'set'
all = Set.new('a'..'z')
puts((1..gets.to_i).reduce(all) { |a, _e| a & Set.new(gets.split('')) }.size)
