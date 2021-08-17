# Definition for singly-linked list.
# class ListNode
#     attr_accessor :val, :next
#     def initialize(val)
#         @val = val
#         @next = nil
#     end
# end

# Producer of random element values drawn from a linked list.
class Solution
  # @param head The linked list's head.
  # Note that the head is guaranteed to be not null, so it contains at least one node.
  # :type head: ListNode
  def initialize(head)
    @elems = []
    while head
      @elems.push(head.val)
      head = head.next
    end
  end

  # Returns a random node's value.
  #:rtype: Integer
  def get_random
    @elems.sample
  end
end

# Your Solution object will be instantiated and called as such:
# obj = Solution.new(head)
# param_1 = obj.get_random()
