# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# @param {ListNode} head
# @return {ListNode}
def insertion_sort_list(head)
  sentinel = ListNode.new(nil)

  while head
    dest = sentinel
    dest = dest.next while dest.next && dest.next.val < head.val

    next_head = head.next
    head.next = dest.next
    dest.next = head
    head = next_head
  end

  sentinel.next
end
