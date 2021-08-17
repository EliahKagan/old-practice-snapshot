<Query Kind="Program" />

private sealed class Node {
    public Node left, right;
    public int data;
    
    public Node(int data, Node left, Node right)
    {
        this.data = data;
        this.left = left;
        this.right = right;
    }
}

private static void levelOrder(Node root)
{
    if (root == null) return;
    var queue = new Queue<Node>(Enumerable.Repeat(root, 1));
    
    do {
        var node = queue.Dequeue();
        Console.Write("{0} ", node.data);
        
        if (node.left != null) queue.Enqueue(node.left);
        if (node.right != null) queue.Enqueue(node.right);
    }
    while (queue.Count != 0);
}

private static void Main()
{
    var root = new Node(3, new Node(2, new Node(1, null, null),
                                       null),
                           new Node(5, new Node(4, null, null),
                                       new Node(7, null, null)));
    //root.Dump();
    levelOrder(root);
}
