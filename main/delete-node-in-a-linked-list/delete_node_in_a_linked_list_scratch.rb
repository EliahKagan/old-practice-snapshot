#!/usr/bin/env ruby
$VERBOSE = true

# Definition for singly-linked list.
class ListNode
  attr_accessor :val, :next
  def initialize(val)
    @val = val
    @next = nil
  end
end

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

# Extension to convert an Array a singly linked list (of ListNode objects).
class Array
  def to_list
    sentinel = ListNode.new(nil)
    cur = sentinel
    each { |val| cur = cur.next = ListNode.new(val) }
    sentinel.next
  end
end

# Extension to print the head address, and all values, of a singly linked list.
class ListNode
  def dump
    display

    head = self
    while head
      print ' ', head.val
      head = head.next
    end

    puts
  end
end

head = (0..7).to_a.to_list
head.dump
delete_node(head)
head.dump
