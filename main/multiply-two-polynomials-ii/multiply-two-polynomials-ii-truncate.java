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
        // We will stop once all the coefficients of higher degree are zero.
        int j = a.length;
        while (j != 0 && a[j - 1] == 0) --j;
        
        // We will create the list front-to-back.
        final Node fake_head = new Node(0);
        
        // Populate and return the list.
        Node cur = fake_head;
        for (int i = 0; i != j; ++i) cur = cur.next = new Node(a[i]);
        return fake_head.next;
    }
    
    private static int[] computeProduct(final int[] a, final int[] b)
    {
        final int[] c = new int[a.length + b.length];
        
        for (int i = 0; i != a.length; ++i)
            for (int j = 0; j != b.length; ++j) c[i + j] += a[i] * b[j];
        
        return c;
    }
    
    Node proOfPolynomials(Node head1, Node head2, int n1, int n2)
    {
        return toList(computeProduct(toArray(head1, n1), toArray(head2, n2)));
    }
}
