require 'set'

def getSet
	Set.new(gets.chomp.split '')
end

gets.to_i.times {puts (getSet & getSet).empty? ? 'NO' : 'YES'}
