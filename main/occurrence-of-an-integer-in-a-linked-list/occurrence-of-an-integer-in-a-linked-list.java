/*
  Return the no. of times search_for value is there in a linked list.
 class Node {
   int value;
 Node next;

  Node(int data) {
   this.data = data;

  }
}
This is method only submission.
You only need to complete the method.
*/
class gfg
{
    int count(Node head, final int key)
    {
        int acc = 0;
        
        for (; head != null; head = head.next)
            if (head.data == key) ++acc;
        
        return acc;
    }
}
