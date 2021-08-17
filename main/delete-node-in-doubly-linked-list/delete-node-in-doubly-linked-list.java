/* Structure of linkedlist
class Node
{
	int data;
	Node next;
	Node prev;
	Node(int d)
	{
		data = d;
		next = prev = null;
	}
}
*/
class GfG
{
    // function returns the head of the linkedlist
    Node deleteNode(final Node head, final Node del)
    {
        if (del.next != null) del.next.prev = del.prev;
        
        if (del.prev == null) return del.next;
        
        del.prev.next = del.next;
        return head;
    }
}

