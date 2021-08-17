def adjacency_list(vertex_count, edges)
  adj = Array.new(vertex_count) { [] }
  edges.each { |src, dest| adj[src] << dest }
  adj
end

def cycle?(adj)
  vis = Array.new(adj.size, :white)

  has_cycle_from = lambda do |src|
    case vis[src]
    when :white
      vis[src] = :gray
      return true if adj[src].any?(&has_cycle_from)
      vis[src] = :black
      false
    when :gray
      true
    when :black
      false
    else
      raise 'Internal error: invalid visitation state!'
    end
  end

  adj.size.times.any?(&has_cycle_from)
end

# @param {Integer} num_courses
# @param {Integer[][]} prerequisites
# @return {Boolean}
def can_finish(num_courses, prerequisites)
  !cycle?(adjacency_list(num_courses, prerequisites))
end
