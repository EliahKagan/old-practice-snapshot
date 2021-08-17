# Disjoint set data structure with union by rank and (full) path compression.
class DisjointSets
  attr_reader :joins

  def initialize(size)
    @elems = Array.new(size, -1)
    @joins = 0
  end

  def union(i, j)
    # find the ancestors and stop if they are already the same
    i = find_set(i)
    j = find_set(j)
    return if i == j

    # unite by rank
    if @elems[i] > @elems[j]
      # j has superior (more negative) rank, so it will be the parent
      @elems[i] = j
    else
      # if i and j have the same rank, promote i
      @elems[i] -= 1 if @elems[i] == @elems[j]

      # i has superior (more negative) rank, so it will be the parent
      @elems[j] = i
    end

    @joins += 1
  end

  private def find_set(i)
    # find the ancestor
    j = i
    j = @elems[j] until @elems[j].negative?

    # compress the path
    until i == j
      parent = @elems[i]
      @elems[i] = j
      i = parent
    end

    j
  end
end

# @param {Integer[]} row
# @return {Integer}
def min_swaps_couples(row)
  sets = DisjointSets.new(row.size / 2)
  row.each_slice(2) { |u, v| sets.union(u / 2, v / 2) }
  sets.joins
end
