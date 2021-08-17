require_relative 'find_the_running_median'

class PriorityQueue
  def to_s
    "#{@compare} #{@elems}"
  end
end

class MedianBag
  def to_s
    "(low{#{@low}}; high{#{@high}})"
  end
end
