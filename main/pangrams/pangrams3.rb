require 'set'
chars = Set.new(gets.downcase.split(''))
puts Set.new('a'..'z').subset?(chars) ? 'pangram' : 'not pangram'
