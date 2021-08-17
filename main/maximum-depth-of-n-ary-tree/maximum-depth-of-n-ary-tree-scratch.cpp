#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class Node {
public:
	int val;
	vector<Node*> children;

	Node() {}

	Node(int _val, vector<Node*> _children) {
		val = _val;
		children = _children;
	}
};

class Solution {
public:
    static int maxDepth(Node* root);
};

int Solution::maxDepth(Node* root)
{
    if (!root) return 0;

    queue<const Node*> q;
    q.push(root);
    auto depth = 0;

    while (!q.empty()) {
        ++depth;

        for (auto breadth = q.size(); breadth != 0u; --breadth) {
            const auto parent = q.front();
            q.pop();

            for (const auto child : parent->children)
                if (child) q.push(child);
        }
    }

    return depth;
}

int main()
{
	Node a {1, {}}, b {2, {}}, c {3, {}}, d {4, {}}, e {5, {}};
	Node f {6, {&a, &b}}, g {7, {&c}}, h {8, {&d, &e}};
	Node i {9, {&f}}, j {10, {&g, &h}};
	Node k {11, {&i, &j}};
	
	cout << Solution::maxDepth(&k) << '\n';

	Node x {100, {}}, y {101, {}}, z {102, {}};
	Node u {103, {&x, &y}}, v {104, {}}, w {105, {&z}};
	Node s {106, {&k, &u, &v, &w}};

	cout << Solution::maxDepth(&s) << '\n';

	Node t {200, {&s}};
	Node r {201, {&t}};

	cout << Solution::maxDepth(&r) << '\n';

	cout << Solution::maxDepth(nullptr) << '\n';
}
