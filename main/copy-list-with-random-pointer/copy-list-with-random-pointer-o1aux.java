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
     * Clones a singly linked list with random pointers (SLLR). This
     * implementation uses O(1) space auxiliary to the input and output SLLRs,
     * but it is not thread-safe.
     * @param head  The head of the initial SLLR. This is temporarily modified.
     * @return The head of the cloned SLLR.
     */
    public Node copyRandomList(final Node head) {
        // Make new nodes and interleave them with the originals in two
        // separate steps, so the original is _less likely_ (albeit still
        // possible) to be modified if an OutOfMemoryError occurs.
        interleave(head, cloneWithoutRandoms(head));

        // Populate the new nodes' random pointers.
        for (Node cur = head; cur != null; cur = cur.next.next) {
            assert cur.next != null :
                    "odd node count populating random pointers";
            assert cur.next.random == null :
                    "random pointer unexpected populated";

            if (cur.random != null) {
                assert cur.random.next != null :
                        "random node lacks interleaved partner";
                cur.next.random = cur.random.next;
            }
        }

        // Separate the SLLRs and return the head of the new SLLR.
        return deinterleave(head);
    }

    /**
     * Clones an SLLR without populating the new SLLR's random pointers.
     * @param head  The head of the initial SLLR to partially clone.
     * @return The head of the cloned SLLR whose random pointers are all null.
     */
    private static Node cloneWithoutRandoms(Node head) {
        final Node outDummy = new Node(0, null, null);
        Node outCur = outDummy;

        for (; head != null; head = head.next) {
            outCur.next = new Node(head.val, null, null);
            outCur = outCur.next;
        }

        return outDummy.next;
    }

    /**
     * Interleaves the nodes of two same-length SLLRs.
     * @param first  The head of the list that will be 1st, 3rd, 5th, etc.
     * @param second  The head of the list that will be 2nd, 4th, 6th, etc.
     */
    private static void interleave(Node first, Node second) {
        final Node outDummy = new Node(0, null, null);
        Node outCur = outDummy;

        while (first != null && second != null) {
            outCur.next = first;
            outCur = outCur.next;
            first = first.next;

            outCur.next = second;
            outCur = outCur.next;
            second = second.next;
        }

        assert first == null : "the first is longer than the second";
        assert second == null : "the second is longer than the first";
        assert outCur.next == null : "the end of the list dangles";
    }

    /**
     * Restores an interleaved SLLR to two separate SLLRs.
     * @return The second head.
     */
    private static Node deinterleave(Node head) {
        final Node outDummy = new Node(0, null, null);
        Node outCur = outDummy;

        while (head != null) {
            assert head.next != null :
                    "odd number of nodes in interleaved SLLR";

            outCur.next = head.next;
            head.next = head.next.next;
            head = head.next;

            outCur = outCur.next;
        }

        outCur.next = null;
        return outDummy.next;
    }
}
