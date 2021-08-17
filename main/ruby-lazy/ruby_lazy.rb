require 'prime'
n = gets.to_i
p Prime.each.lazy.select { |k| ->(s) { s == s.reverse }.call(k.to_s) }.first(n)
