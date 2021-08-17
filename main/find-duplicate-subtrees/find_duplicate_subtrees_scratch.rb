# Definition for a binary tree node.
class TreeNode
  attr_accessor :val, :left, :right
  def initialize(val)
    @val = val
    @left, @right = nil, nil
  end
end

# @param {TreeNode} root
# @return {TreeNode[]}
def find_duplicate_subtrees(root)
  ids = {}    # [val, left id #, right id #] -> id #
  nodes = []  # id # -> a representative subroot
  duped = []  # duped[i] is true iff id # i is duped

  identify = lambda do |node|
    return -1 unless node

    key = [node.val,
           identify.call(node.left),
           identify.call(node.right)].freeze

    if (i = ids[key])
      duped[i] = true # was found, so this dupes it
    else
      ids[key] = i = nodes.size
      nodes << node
      duped << false # not yet duped
    end
    i
  end

  identify.call(root)
  nodes.lazy.zip(duped).select(&:last).map(&:first)
end
