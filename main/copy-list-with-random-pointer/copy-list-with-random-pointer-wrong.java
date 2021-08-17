/*
// Definition for a Node.
class Node {
    public int val;
    public Node next;
    public Node random;

    public Node() {}

    public Node(int _val,Node _next,Node _random) {
        val = _val;
        next = _next;
        random = _random;
    }
};
*/
class Solution {
    /**
     * Clones a singly linked list with random pointers (SLLR).
     * @param head  The head of the initial SLLR.
     * @return The head of the cloned SLLR.
     */
    public Node copyRandomList(Node head) {
        final Map<Node, Node> nodes = new HashMap<>(); // (old -> new) mappings
        final Node newHead = cloneWithoutRandoms(head, nodes);
        populateRandoms(nodes, head, newHead);
        return newHead;
    }

    /**
     * Clones an SLLR without populating the new SLLR's random pointers,
     * recording mappings from original node to cloned nodes.
     * @param head  The head of the initial SLLR to partially clone.
     * @param nodes  The map in which to record (old -> new) for all nodes.
     * @return The head of the clones SLLR whose random points are all null.
     */
    private static Node
    cloneWithoutRandoms(Node head, final Map<Node, Node> nodes) {
        final Node outDummy = new Node(0, null, null);
        Node outCur = outDummy;

        for (; head != null; head = head.next) {
            outCur.next = new Node(head.val, null, null);
            outCur = outCur.next;
            nodes.put(head, outCur);
        }

        return outDummy.next;
    }

    /**
     * Populates random pointers to a destination SLLR to finish cloning.
     * @param nodes  The map with (old -> new) mappings for all nodes.
     * @param orig  The head of the original SLLR, with intact random pointers.
     * @param copy  The head of the new SLLR, which needs random pointers.
     */
    private static void
    populateRandoms(final Map<Node, Node> nodes, Node orig, Node copy) {
        while (orig != null && copy != null) {
            assert copy.random == null : "random unexpectedly set";

            if (copy.random != null) {
                orig.random = nodes.get(copy.random);
                assert orig.random != null : "random unexpectedly unset";
            }

            orig = orig.next;
            copy = copy.next;
        }

        assert orig == null && copy == null : "lists differ in length";
    }
}
