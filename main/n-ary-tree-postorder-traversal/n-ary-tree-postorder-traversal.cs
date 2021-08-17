/*
// Definition for a Node.
public class Node {
    public int val;
    public IList<Node> children;

    public Node(){}
    public Node(int _val,IList<Node> _children) {
        val = _val;
        children = _children;
}
*/
public class Solution {
    public IList<int> Postorder(Node root) {
        var ret = new List<int>();
        if (root == null) return ret;

        var stack = new Stack<Frame>();
        stack.Push(new Frame(root));

        while (stack.Count != 0) {
            var frame = stack.Peek();

            if (frame.Index == frame.Parent.children.Count) {
                ret.Add(frame.Parent.val);
                stack.Pop();
            } else {
                stack.Push(new Frame(frame.Parent.children[frame.Index++]));
            }
        }

        return ret;
    }

    private sealed class Frame {
        internal Frame(Node parent) => Parent = parent;

        internal Node Parent { get; }
        internal int Index { get; set; } = 0;
    }
}
