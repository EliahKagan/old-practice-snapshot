/**
 * Definition for singly-linked list.
 * public class ListNode {
 *     public int val;
 *     public ListNode next;
 *     public ListNode(int x) { val = x; }
 * }
 */

public class Solution {
    /// <summary>Mergesorts a singly linked list. O(1) extra space.</summary>
    /// <param name="head">The head of the list (or null if empty).</param>
    /// <returns>The head of the list, whose nodes are rearranged.</returns>
    public ListNode SortList(ListNode head)
    {
        for (var length = 1; ; length *= 2) {
            var newHead = MergePass(head, length);
            if (newHead == null) break;
            head = newHead;
        }

        return head;
    }

    /// <summary>Merges pairs of sublists of a specified length.</summary>
    /// <param name="head">The head of the list (or null if empty).</param>
    /// <param name="length">The length of each sublist to merge.</param>
    /// <returns>
    /// The head of list of merged nodes, or <c>null</c> if there was no
    /// merging to do because the list had no more than <c>length</c> nodes.
    /// </returns>
    private static ListNode MergePass(ListNode head, int length)
    {
        EnsureLengthPositive(length);

        var sentinel = new ListNode(0);
        sentinel.next = head;
        var beforeFirst = sentinel;

        for (; ; ) {
            var beforeSecond = Advance(beforeFirst, length);
            var second = beforeSecond?.next;
            if (second == null) break; // no second sequence to merge with
            beforeSecond.next = null;

            var beforeThird = Advance(second, length - 1);
            var third = beforeThird?.next;
            if (third != null) beforeThird.next = null;

            var (newFirst, newLast) = Merge(beforeFirst.next, second);
            beforeFirst.next = newFirst;
            newLast.next = third;
            beforeFirst = newLast;
        }

        return beforeFirst == sentinel ? null : sentinel.next;
    }

    /// <summary>
    /// Merges two acyclic non-overlapping singly linked lists, that should
    /// themselves already be sorted and nonempty, in stably sorted order.
    /// </summary>
    /// <param name="first">The head of the first list.</param>
    /// <param name="second">The head of the second list.</param>
    /// <returns>A pair of the merged list's first and last nodes.</returns>
    private static (ListNode, ListNode) Merge(ListNode first, ListNode second)
    {
        var sentinel = new ListNode(0);
        var cur = sentinel;

        for (; first != null && second != null; cur = cur.next) {
            if (second.val < first.val) {
                cur.next = second;
                second = second.next;
            } else {
                cur.next = first;
                first = first.next;
            }
        }

        cur.next = (first == null ? second : first);
        while (cur.next != null) cur = cur.next;

        return (sentinel.next, cur);
    }


    /// <summary>Advances in the list by specified number of nodes.</summary>
    /// <param name="node">The node to start from.</param>
    /// <param name="len">The length (number of nodes) to advance.</param>
    /// <returns>
    /// The node <c>len</c> nodes past <c>node</c>, or <c>null</c> if there is
    /// no such node or if <c>node</c> was <c>null</c>.
    /// </returns>
    private static ListNode Advance(ListNode node, int len)
    {
        for (; node != null && len != 0; --len) node = node.next;
        return node;
    }

    /// <summary>Throws an exception if <c>length</c> is nonpositive.</summary>
    /// <param name="length">The parameter whose value is checked.</param>
    private static void EnsureLengthPositive(int length)
    {
        if (length <= 0) {
            throw new ArgumentOutOfRangeException(nameof(length),
                    $"{nameof(length)} must be (strictly) positive");
        }
    }
}
