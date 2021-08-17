#!/usr/bin/env ruby
$VERBOSE = true

# A key-value pair for associative containers like the PrimHeap.
KeyValuePair = Struct.new(:key, :value)

# An associative binary minheap augmented with include? and decrease methods.
class PrimHeap
  def initialize
    @table = {} # key -> index
    @heap = []  # index -> (key, value)
  end

  def empty?
    @heap.empty?
  end

  def one?
    @heap.one?
  end

  def size
    @heap.size
  end

  alias length size
  alias count size

  def push(key, value)
    raise 'attempt to add duplicate key' if include?(key)

    child = size
    @heap.push(KeyValuePair.new(key, value))
    heapify_up(child)

    self
  end

  def peek
    @heap.first
  end

  alias first peek

  def pop
    if size < 2
      @table.clear
      @heap.shift
    else
      ret = peek
      @table.delete(ret.key)

      @heap[0] = @heap.pop
      heapify_down(0)

      ret
    end
  end

  def include?(key)
    @table.include?(key)
  end

  alias has_key? include?

  def [](key)
    index = @table[key]
    index.nil? ? nil : @heap[index].value
  end

  def decrease(key, value)
    child = @table[key]
    raise ArgumentError, 'key absent' if child.nil?

    entry = @heap[child]
    raise ArgumentError, 'attempt to increase value' if entry.value < value

    entry.value = value
    heapify_up(child)

    self
  end

  private def heapify_up(child)
    while child.nonzero?
      parent = (child - 1) / 2
      break if order_ok?(parent, child)

      swap(child, parent)
      child = parent
    end

    record(child)
  end

  private def heapify_down(parent)
    loop do
      child = pick_child(parent)
      break if child.nil? || order_ok?(parent, child)

      swap(parent, child)
      parent = child
    end

    record(parent)
  end

  private def pick_child(parent)
    left = parent * 2 + 1
    return nil if left >= size

    right = left + 1
    right == size || order_ok?(left, right) ? left : right
  end

  private def order_ok?(parent, child)
    @heap[parent].value <= @heap[child].value
  end

  private def swap(src, dest)
    tmp = @heap[dest]
    @heap[dest] = @heap[src]
    @heap[src] = tmp

    record(src)
  end

  private def record(src)
    @table[@heap[src].key] = src
  end
end
