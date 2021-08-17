#!/usr/bin/env ruby
$VERBOSE = true

unless Enumerable.method_defined?(:sum)
  # Define a quick and dirty sum (assumes integers and no block).
  module Enumerable
    def sum
      reduce(0, :+)
    end
  end
end

# Disjoint sets implemented via union by size with full path compression.
class DisjointSets
  def initialize(vertex_count)
    @elems = Array.new(vertex_count, -1)
  end

  # Get the sizes of each connected component.
  def sizes
    @elems.select(&:negative?).map!(&:-@)
  end

  def union(i, j)
    # find what sets they are in, and stop if they are already joined
    i = find(i)
    j = find(j)
    return if i == j

    # unite the sets by size (which is stored negated)
    if @elems[i] < @elems[j]
      join(i, j) # set i is bigger, so have it absorb set j
    else
      join(j, i) # set j is bigger (or same size), so have it absorb set i
    end

    nil
  end

  private def find(i)
    # find the ancestor
    j = i
    j = @elems[j] while @elems[j] >= 0

    # compress the path
    i, @elems[i] = @elems[i], j while i != j # FIXME: not parallel assignment?!

    j
  end

  private def join(parent, child)
    @elems[parent] += @elems[child]
    @elems[child] = parent
  end
end

def read_sets(vertex_count, edge_count)
  sets = DisjointSets.new(vertex_count)

  edge_count.times do
    u, v, color = gets.split
    sets.union(u.to_i, v.to_i) if color == 'b'
  end

  sets
end

MOD = 10**9 + 7

def count_pairs(sizes)
  sum = sizes.sum
  sizes.map { |size| size * (sum -= size) }
end

def count_triplets(sizes)
  pair_counts = count_pairs(sizes)
  sum = pair_counts.sum

  sizes.lazy.zip(pair_counts).map do |size, pair_count|
    size * (sum -= pair_count) % MOD
  end
end

if $PROGRAM_NAME == __FILE__
  n = gets.to_i
  sets = read_sets(n + 1, n - 1) # not using vertex 0, so n + 1 vertices
  sizes = sets.sizes
  sizes.shift # not using vertex 0
  puts count_triplets(sizes).sum % MOD
end
