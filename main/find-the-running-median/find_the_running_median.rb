#!/usr/bin/env ruby
$VERBOSE = true

# A priority queue implemented as a heap. By default it is a minheap.
class PriorityQueue
  def self.create_minheap
    PriorityQueue.new
  end

  def self.create_maxheap
    PriorityQueue.new(:>=)
  end

  def initialize(compare = :<=)
    @compare = compare
    @elems = []
  end

  def empty?
    @elems.empty?
  end

  def size
    @elems.size
  end

  def push(item)
    last = size
    @elems.push(item)
    heapify_up(last)
  end

  def peek
    @elems[0]
  end

  def pop
    return @elems.pop if size < 2

    item = @elems[0]
    @elems[0] = @elems.pop
    heapify_down(0)
    item
  end

  private def heapify_up(child)
    while child.nonzero?
      parent = (child - 1) / 2
      break if order_ok?(parent, child)
      swap(parent, child)
      child = parent
    end
  end

  private def heapify_down(parent)
    loop do
      child = pick_child(parent)
      break if child.nil? || order_ok?(parent, child)
      swap(parent, child)
      parent = child
    end
  end

  private def pick_child(parent)
    left = parent * 2 + 1
    return nil if left >= size
    right = left + 1
    right == size || order_ok?(left, right) ? left : right
  end

  private def order_ok?(i, j)
    @elems[i].send(@compare, @elems[j])
  end

  private def swap(i, j)
    @elems[i], @elems[j] = @elems[j], @elems[i]
  end
end

# A bag of numbers that supports efficient computation of the median.
# Supports adding new values but does not support removing them.
class MedianBag
  def initialize
    @low = PriorityQueue.create_maxheap
    @high = PriorityQueue.create_minheap
  end

  def add(value)
    (@low.empty? || @low.peek > value ? @low : @high).push(value)
    rebalance
  end

  def median
    delta = size_delta

    if delta.zero?
      (@low.peek + @high.peek) / 2.0
    elsif delta == -1
      @low.peek
    elsif delta == +1
      @high.peek
    else
      raise 'Internal error: balancing invariant violated'
    end
  end

  private def rebalance
    delta = size_delta

    if delta == -2
      @high.push(@low.pop)
    elsif delta == +2
      @low.push(@high.pop)
    end
  end

  private def size_delta
    @high.size - @low.size
  end
end

if $PROGRAM_NAME == __FILE__
  bag = MedianBag.new

  gets.to_i.times do
    bag.add(gets.to_i)
    printf "%.1f\n", bag.median
  end
end
