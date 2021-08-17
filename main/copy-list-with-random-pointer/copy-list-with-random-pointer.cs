/**
 * Definition for singly-linked list with a random pointer.
 * public class RandomListNode {
 *     public int label;
 *     public RandomListNode next, random;
 *     public RandomListNode(int x) { this.label = x; }
 * };
 */
public class Solution {
    public RandomListNode CopyRandomList(RandomListNode head) {
        if (head == null) return null;

        // Create a list of unconnected copies.
        var copies = new Dictionary<RandomListNode, RandomListNode>();
        for (var orig = head; orig != null; orig = orig.next)
            copies.Add(orig, new RandomListNode(orig.label));

        // Solves the problem of Dictionary<,> not supporting null keys.
        RandomListNode GetCopy(RandomListNode orig)
            => orig == null ? null : copies[orig];

        // Connect the copies.
        for (var orig = head; orig != null; orig = orig.next) {
            var copy = copies[orig];
            copy.next = GetCopy(orig.next);
            copy.random = GetCopy(orig.random);
        }

        return copies[head];
    }
}
