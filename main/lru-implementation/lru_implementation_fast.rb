#!/usr/bin/env ruby
$VERBOSE = true

# An inspectable cache of just keys, using least-recently-used invalidation.
# This code takes advantage of how the Hash type in Ruby 1.9 and higher is
# officially guaranteed to maintain insertion order. (In MRI 1.9+ they happen
# to be implemented the same way I would otherwise implement an LRU cache: by
# maintaining both a hash table and circular doubly linked list.)
class LRUCache
  attr_reader :misses

  def initialize(capacity)
    raise ArgumentError, 'capacity must be positive' unless capacity.positive?
    @capacity = capacity
    @queue = {} # so we can use Hash#shift (there is no Set#shift)
    @misses = 0
  end

  def to_s
    @queue.keys.reverse.join(' ')
  end

  def bump(key)
    unless @queue.delete(key)
      @queue.shift if @queue.size == @capacity
      @misses += 1
    end
    @queue[key] = true
  end
end

cache = LRUCache.new(gets.split.last.to_i) # don't need n
$stdin.read.split.lazy.map(&:to_i).each { |key| cache.bump(key) }
puts cache.misses, cache
