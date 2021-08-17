require 'set'

def pangram?(text)
  Set.new('a'..'z').subset?(Set.new(text.downcase.split('')))
end

puts pangram?(gets) ? 'pangram' : 'not pangram'
