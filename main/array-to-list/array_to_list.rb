# Definition for singly-linked list.
class ListNode
  attr_accessor :val, :next
  def initialize(val)
    @val = val
    @next = nil
  end
end

# Extension to convert an Array a singly linked list (of ListNode objects).
class Array
  def to_list
    sentinel = ListNode.new(nil)
    cur = sentinel
    each { |val| cur = cur.next = ListNode.new(val) }
    sentinel.next
  end
end
