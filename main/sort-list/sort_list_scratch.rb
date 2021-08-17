# frozen_string_literal: true

# Definition for singly-linked list.
class ListNode
  attr_accessor :val, :next

  def initialize(val)
    @val = val
    @next = nil
  end
end

# @param {ListNode} head
# @return {ListNode}
def sort_list(head)
  length = 1

  loop do
    new_head = merge_pass(head, length)
    return head if new_head.nil?

    head = new_head
    length *= 2
  end
end

def merge_pass(head, length)
  sentinel = ListNode.new(false)
  sentinel.next = head
  before_first = sentinel

  loop do
    before_second = advance(before_first, length)
    second = before_second&.next
    break if second.nil? # no second half to merge
    before_second.next = nil

    before_third = advance(second, length - 1)
    third = before_third&.next
    before_third.next = nil unless third.nil?

    before_first.next, last = *merge(before_first.next, second)
    last.next = third
    before_first = last
  end

  before_first.equal?(sentinel) ? nil : sentinel.next
end

def advance(node, distance)
  distance.times do
    break if node.nil?
    node = node.next
  end

  node
end

def merge(first, second)
  sentinel = ListNode.new(false)
  cur = sentinel

  until first.nil? || second.nil?
    if second.val < first.val
      cur.next = second
      second = second.next
    else
      cur.next = first
      first = first.next
    end
    cur = cur.next
  end

  cur.next = (second.nil? ? first : second)
  cur = cur.next until cur.next.nil?

  [sentinel.next, cur]
end
