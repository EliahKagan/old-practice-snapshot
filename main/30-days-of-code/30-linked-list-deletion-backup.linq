<Query Kind="Program" />

private sealed class Node {
    public int data;
    public Node next;
    
    public Node(int data, Node next)
    {
        this.data = data;
        this.next = next;
    }
}

private static void print(Node head)
{
    if (head == null) Console.WriteLine();
    else {
        Console.Write("{0} ", head.data);
        print(head.next);
    }
}

private static Node removeDuplicates(Node head)
{
    for (var node = head; node != null && node.next != null;
                          node = node.next) {
        if (node.data == node.next.data) node.next = node.next.next;
    }
    
    return head;
}

private static void Main()
{
    var head = new Node(1,
                new Node(2,
                    new Node(2,
                        new Node(3,
                            new Node(3,
                                new Node(4, null))))));
    
    print(head);
    print(removeDuplicates(head));
    print(head);
    
    print(null);
    print(removeDuplicates(null));
    Console.WriteLine("Done.");
}
