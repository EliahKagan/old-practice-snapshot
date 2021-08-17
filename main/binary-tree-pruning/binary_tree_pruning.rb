# Definition for a binary tree node.
# class TreeNode
#     attr_accessor :val, :left, :right
#     def initialize(val)
#         @val = val
#         @left, @right = nil, nil
#     end
# end

# @param {TreeNode} root
# @return {TreeNode}
def prune_tree(root)
  return nil unless root
  root.left = prune_tree(root.left)
  root.right = prune_tree(root.right)
  root.left || root.right || root.val.nonzero? ? root : nil
end
