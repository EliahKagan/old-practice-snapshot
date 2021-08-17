""" Node is defined as
class node:
  def __init__(self, data):
      self.data = data
      self.left = None
      self.right = None
"""

def traverse_inorder(root):
    if root is not None:
        yield from traverse_inorder(root.left)
        yield root.data
        yield from traverse_inorder(root.right)

def check_binary_search_tree_(root):
    a = list(traverse_inorder(root))
    return all(a[i - 1] < a[i] for i in range(1, len(a)))
