def adjacency_list(vertex_count, edges)
  adj = Array.new(vertex_count) { [] }
  edges.each { |src, dest| adj[src] << dest }
  adj
end

def cycle?(adj)
  vis = Array.new(adj.size, :white)

  dfs = proc do |src|
    next if vis[src] == :black
    raise 'Internal error: corrupted visitation list' if vis[src] != :white
    vis[src] = :gray
    path = [src]

    until path.empty?
      row = adj[path.last]
      if row.empty?
        vis[path.pop] = :black
        next
      end

      dest = row.shift
      case vis[dest]
      when :white
        vis[dest] = :gray
        path << dest
      when :gray
        return true # this is why dfs is a traditional proc and not a lambda
      when :black
        next # do nothing, we don't need to revisit explored territory
      else
        raise 'Internal error: invalid visitation state'
      end
    end
  end

  adj.size.times(&dfs) # returns true from the proc if a cycle is found
  false
end

# @param {Integer} num_courses
# @param {Integer[][]} prerequisites
# @return {Boolean}
def can_finish(num_courses, prerequisites)
  !cycle?(adjacency_list(num_courses, prerequisites))
end
