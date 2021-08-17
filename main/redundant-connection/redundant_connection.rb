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

# @param {Integer[][]} edges
# @return {Integer[]}
def find_redundant_connection(edges)
  sets = DisjointSets.new(edges.length + 1) # because we're not using 0

  edges.each do |edge|
    return edge unless sets.union(*edge)
  end

  nil
end
