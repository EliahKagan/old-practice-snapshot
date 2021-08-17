/**
 * Definition for a binary tree node.
 * public class TreeNode {
 *     public int val;
 *     public TreeNode left;
 *     public TreeNode right;
 *     public TreeNode(int x) { val = x; }
 * }
 */
public class Codec {
    // Encodes a tree to a single string.
    public string serialize(TreeNode root) {
        if (root == null) return "";

        var indices = new Dictionary<TreeNode, int>();
        var nodes = new List<TreeNode>();

        void dfs(TreeNode node) {
            indices.Add(node, nodes.Count);
            nodes.Add(node);
            if (node.left != null) dfs(node.left);
            if (node.right != null) dfs(node.right);
        }
        dfs(root);

        var sb = new StringBuilder();

        foreach (var node in nodes) {
            sb.Append(node.val);
            sb.Append(',');
            if (node.left != null) sb.Append(indices[node.left]);
            sb.Append(',');
            if (node.right != null) sb.Append(indices[node.right]);
            sb.Append(';');
        }
        sb.Length -= 1; // remove the final ";" separator

        return sb.ToString();
    }

    // Decodes your encoded data to tree.
    public TreeNode deserialize(string data) {
        if (data.Length == 0) return null;

        var reprs = Array.ConvertAll(data.Split(';'), tok => tok.Split(','));
        var nodes = Array.ConvertAll(reprs,
                                     repr => new TreeNode(int.Parse(repr[0])));

        foreach (var i in Enumerable.Range(0, reprs.Length)) {
            if (reprs[i][1].Length != 0)
                nodes[i].left = nodes[int.Parse(reprs[i][1])];
            if (reprs[i][2].Length != 0)
                nodes[i].right = nodes[int.Parse(reprs[i][2])];
        }

        return nodes[0];
    }
}

// Your Codec object will be instantiated and called as such:
// Codec codec = new Codec();
// codec.deserialize(codec.serialize(root));
