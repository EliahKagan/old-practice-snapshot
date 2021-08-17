require 'set'

def getchars
  Set.new(gets.chomp.split(''))
end

gets.to_i.times do
  puts((getchars & getchars).empty? ? 'NO' : 'YES')
end
