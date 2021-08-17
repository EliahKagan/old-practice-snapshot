require 'set'
chars = Set.new('a'..'z')
gets.to_i.times { chars &= Set.new(gets.split('')) }
puts chars.size
