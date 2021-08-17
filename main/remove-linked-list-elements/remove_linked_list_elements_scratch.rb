# Definition for singly-linked list.
class ListNode
  attr_accessor :val, :next
  def initialize(val)
    @val = val
    @next = nil
  end
end

# @param {ListNode} head
# @param {Integer} val
# @return {ListNode}
def remove_elements(head, val)
  sentinel = ListNode.new(nil)
  sentinel.next = head

  cur = sentinel
  while cur.next
    if cur.next.val == val
      cur.next = cur.next.next
    else
      cur = cur.next
    end
  end

  sentinel.next
end
