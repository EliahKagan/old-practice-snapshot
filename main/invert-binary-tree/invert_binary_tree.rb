# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

def flip(root)
  return unless root

  root.left, root.right = root.right, root.left
  flip(root.left)
  flip(root.right)
end

# @param {TreeNode} root
# @return {TreeNode}
def invert_tree(root)
  flip(root)
  root
end
