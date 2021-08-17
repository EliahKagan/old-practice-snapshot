require 'prime'

gets.to_i.times do
  limit = gets.to_i
  product = 1
  count = 0

  Prime.each do |prime|
    product *= prime
    break if product > limit
    count += 1
  end

  puts count
end
