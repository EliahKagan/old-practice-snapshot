#!/usr/bin/env ruby
$VERBOSE = true

# A node for a circular doubly linked list.
class Node
  attr_reader :left, :right
  attr_accessor :key

  def initialize(key = nil)
    @left = @right = self
    @key = key
  end

  # Creates an array of this list's values. Treats self as a sentinel node.
  def to_a
    ret = []

    cur = self
    while (cur = cur.right) != self
      ret.push(cur.key)
    end

    ret
  end

  def splice_right(node)
    node.detach

    node.right = @right
    node.left = self

    @right = @right.left = node
  end

  protected

  attr_writer :left, :right

  def detach
    @left.right = @right
    @right.left = @left

    @left = @right = self
  end
end

# An inspectable cache of just keys, using least-recently-used invalidation.
class LRUCache
  def initialize(capacity)
    raise ArgumentError, 'capacity must be positive' unless capacity.positive?
    @capacity = capacity
    @size = 0
    @queue = Node.new # sentinel node
    @table = {} # maps keys to nodes
  end

  def to_a
    @queue.to_a
  end

  # Sets key as the priority element, inserting it if it is not present.
  # Returns true iff the key had to be added (a page fault / cache miss).
  def bump(key)
    node = @table[key]
    miss = node.nil?

    if miss
      if @size == @capacity
        node = @queue.left
        @table.delete(node.key)
        node.key = key
        @table[key] = node
      else
        raise 'Internal error: size exceeds capacity!' unless @size < @capacity
        @size += 1
        @table[key] = node = Node.new(key)
      end
    end

    @queue.splice_right(node)
    miss
  end
end

cache = LRUCache.new(gets.split.last.to_i) # don't need n
puts($stdin.read.split.lazy.map(&:to_i).count { |key| cache.bump(key) })
puts cache.to_a.join(' ')
