#!/usr/bin/env ruby
$VERBOSE = true

# Disjiont set data structure with union by rank and path compression.
class DisjointSets
  def initialize(size)
    @elems = Array.new(size, -1)
  end

  def union(i, j)
    # Find the ancestors and check if they are already in the same set.
    i = find(i)
    j = find(j)
    return false if i == j

    # Unite the sets by rank.
    if @elems[i] > @elems[j]
      # j has superior (more negative) rank.
      @elems[i] = j
    else
      # If i and j have the same rank, promote i.
      @elems[i] -= 1 if @elems[i] == @elems[j]

      # i has superior (more negative) rank.
      @elems[j] = i
    end

    true
  end

  private def find(i)
    # Find the ancestor.
    j = i
    j = @elems[j] while @elems[j] >= 0

    # Compress the path.
    while i != j
      p = @elems[i]
      @elems[i] = j
      i = p
    end

    j
  end
end

# A weighted directed edge.
class Edge
  attr_reader :u, :v, :w

  def initialize(u, v, w)
    @u = u
    @v = v
    @w = w
  end
end

def read_record
  gets.split.map(&:to_i)
end

vertex_count, edge_count = read_record
sets = DisjointSets.new(vertex_count + 1) # because we're not using 0
edges = (1..edge_count).map { Edge.new(*read_record) }.sort_by!(&:w)
puts edges.reduce(0) { |a, e| sets.union(e.u, e.v) ? a + e.w : a }
