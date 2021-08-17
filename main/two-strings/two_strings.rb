require 'set'
a_to_z = Set.new('a'..'z').freeze

gets.to_i.times do
  chars = [gets, gets].reduce(a_to_z) { |a, e| a & Set.new(e.chomp.split('')) }
  puts chars.empty? ? 'NO' : 'YES'
end
