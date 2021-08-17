# methods supporting string rotation for trivial monoalphabetic ciphers
class String
  BIAS_LOWER, BIAS_UPPER = %w(a A).map(&:ord)
  LOWER, UPPER = ['a'..'z', 'A'..'Z'].map(&:to_a).map(&:freeze)

  def rot_in(bias, alphabet, key)
    alphabet[(ord - bias + key) % 26]
  end

  def rot(key) # "encrypts" a single character
    case self
    when /\A[a-z]\z/ then rot_in(BIAS_LOWER, LOWER, key)
    when /\A[A-Z]\z/ then rot_in(BIAS_UPPER, UPPER, key)
    else self
    end
  end

  def rotate(key) # "encrypts" a whole string, in place
    (0...size).each { |index| self[index] = self[index].rot(key) }
    self
  end
end

def read_cleartext
  size = gets.to_i
  str = gets.chomp
  raise 'cleartext input not of specified length' unless str.size == size
  str
end

puts read_cleartext.rotate(gets.to_i)
