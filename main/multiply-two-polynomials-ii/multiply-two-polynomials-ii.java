/* Linked List Node
class Node
{
	int data;
	Node next;
	
	Node(int d)
	{
		data = d;
		next = null;
	}
}*/

final class GfG {
    private static int[] toArray(Node head, final int length)
    {
        final int[] a = new int[length];
        
        for (int i = 0; i != length; ++i) {
            if (head == null) break;
            a[i] = head.data;
            head = head.next;
        }
        
        return a;
    }
    
    private static Node toList(final int[] a)
    {
        final Node fake_head = new Node(0);
        
        Node cur = fake_head;
        for (int i = 0; i != a.length; ++i) cur = cur.next = new Node(a[i]);
        
        return fake_head.next;
    }
    
    private static int[] computeProduct(final int[] a, final int[] b)
    {
        final int[] c = new int[a.length + b.length - 1];
        
        for (int i = 0; i != a.length; ++i)
            for (int j = 0; j != b.length; ++j) c[i + j] += a[i] * b[j];
        
        return c;
    }
    
    Node proOfPolynomials(Node head1, Node head2, int n1, int n2)
    {
        return toList(computeProduct(toArray(head1, n1), toArray(head2, n2)));
    }
}
