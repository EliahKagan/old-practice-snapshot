require 'set'

# balanced? method, and supporting constants, to check if groupers are balanced
class String
  GROUPERS = { '(' => ')', '[' => ']', '{' => '}' }.freeze
  CLOSERS = Set.new(GROUPERS.values).freeze

  def balanced?
    closer_stack = []

    each_char do |char|
      if (closer = GROUPERS[char])
        closer_stack.push(closer)
      elsif CLOSERS.include?(char)
        return false unless closer_stack.pop == char
      end
    end

    !closer_stack.pop # only balanced if all are closed
  end
end

gets.to_i.times { puts gets.balanced? ? 'YES' : 'NO' }
