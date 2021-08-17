require 'set'

def pangram?(text)
  str = text.downcase
  Set.new('a'..'z').subset?(Set.new((0..str.size).map { |index| str[index] }))
end

puts pangram?(gets) ? 'pangram' : 'not pangram'
