# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} node
# @return {Void} Do not return anything, modify node in-place instead.
def delete_node(node)
  return unless node.next

  loop do
    node.val = node.next.val
    break unless node.next.next
    node = node.next
  end

  node.next = nil
end
