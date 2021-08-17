# Tracks frequencies of items, indicating if a goal has been reached.
class Counter
  def initialize(goal)
    @counts = Hash.new(0)
    @total = 0

    goal.each do |item|
      @counts[item] -= 1
      @total -= 1
    end

    @counts.default = nil
  end

  def add(item)
    @total += 1 if @counts.include?(item) && (@counts[item] += 1) <= 0
  end

  def delete(item)
    @total -= 1 if @counts.include?(item) && (@counts[item] -= 1).negative?
  end

  def at_goal?
    @total.zero?
  end
end

def min_window_from_counter(s, targets)
  range = -Float::INFINITY...0

  right = 0
  (0...s.size).each do |left|
    until targets.at_goal? || right == s.size
      targets.add(s[right])
      right += 1
    end

    break unless targets.at_goal?

    range = left...right if right - left < range.size
    targets.delete(s[left])
  end

  range.first.negative? ? '' : s[range]
end

# @param {String} s
# @param {String} t
# @return {String}
def min_window(s, t)
  if s.empty?
    ''
  elsif t.empty?
    s[0]
  else
    min_window_from_counter(s, Counter.new(t.each_char))
  end
end
