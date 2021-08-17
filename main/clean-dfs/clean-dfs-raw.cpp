// "Iterative" DFS that uses a stack of *just* the nodes traversed to arrive at
// the node being currently visited. When the target node is found, the stack
// is a path from the root to it; if the target node is not present, the stack
// is empty after the entire tree is traversed. Thus the stack is returned to
// the caller, indicating if the target is present, the identity of the target
// node, and the identity of all the nodes along the path that was found from
// the root to the target.

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <stack>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace { // supporting types and functions
    // Enumeration representing the left or right branch of a tree.
    enum class Side { left, right };

    // Reads a character from an input stream, interpreting it as a Side value.
    std::istream& operator>>(std::istream& in, Side& side)
    {
        auto c = '\0';

        if (in >> c) {
            switch (c) {
            case 'L':
                side = Side::left;
                break;

            case 'R':
                side = Side::right;
                break;

            default:
                in.setstate(std::ios_base::failbit);
            }
        }

        return in;
    }

    // Structure representing a parent-child relationship between nodes in a
    // binary tree.
    template<typename T>
    struct Connection {
        T parent {}, child {};
        Side side {};
    };

    // Reads two integers and a character from an input stream, interpreting
    // them as the value of a Connection structure.
    template<typename T>
    std::istream& operator>>(std::istream& in, Connection<T>& con)
    {
        return in >> con.parent >> con.child >> con.side;
    }

    // Reads as many Connection structures as possible from one line of input.
    template<typename T>
    std::vector<Connection<T>> read_connections()
    {
        std::string line;
        std::getline(std::cin, line);
        std::istringstream in {line};

        std::vector<Connection<T>> a;
        for (Connection<T> con; in >> con; ) a.push_back(con);
        return a;
    }

    // A node in a binary tree.
    template<typename T>
    struct Node { // TODO: Use std::unique_ptr<Node<T>> instead of Node<T>*.
        T data {};
        Node* left {};
        Node* right {};
    };

    // Gets the node of the given data from the map, creating it if necessary.
    template<typename T>
    Node<T>* get_node(std::unordered_map<T, Node<T>*>& nodes, const T& data)
    {
        const auto p = nodes.find(data);
        if (p != nodes.end()) return p->second;

        const auto node = new Node<T>{data, nullptr, nullptr};
        nodes.emplace(data, node);
        return node;
    }

    // Like get_node(), but ensures the node being retrieved or created is not
    // yet a child, then records it as being one.
    template<typename T>
    Node<T>* get_node_as_new_child(std::unordered_map<T, Node<T>*>& nodes,
            std::unordered_set<Node<T>*>& children, const T& data)
    {
        const auto child_node = get_node(nodes, data);

        if (children.find(child_node) != children.end())
            throw std::invalid_argument{"a node's parent must be unique"};

        children.insert(child_node);
        return child_node;
    }

    // Obtains a reference to the child pointer (of node) indicated by side.
    template<typename T>
    Node<T>*& child_at(Node<T>* const node, const Side side)
    {
        switch (side) {
        case Side::left:
            return node->left;

        case Side::right:
            return node->right;
        }

        throw std::out_of_range{"invalid value of Side enumeration!"};
    }

    // Like child_at(), but throws an exception if the referenced child pointer
    // is non-null, so the returned reference is always a valid destination for
    // a new child pointer.
    template<typename T>
    Node<T>*& child_dest(Node<T>* const node, const Side side)
    {
        auto& dest = child_at(node, side);

        if (dest != nullptr) {
            throw std::invalid_argument{
                    "a node's child must be unique on each side"};
        }

        return dest;
    }

    // Throws an exception if the root is invalid due to being a child node.
    template<typename T>
    void validate_root(Node<T>* const root,
                       const std::unordered_set<Node<T>*>& children)
    {
        if (children.find(root) != children.cend())
            throw std::invalid_argument{"the root node must not have a parent"};
    }

    // Constructs a tree from a vector of Connnection structures.
    //
    // CAUTION: Silently accepts a forest, leaking all but the first tree.
    //
    // CAUTION: Leaks memory if exceptions are thrown (the intended use case
    //          involves terminating the application if the calls fails).
    template<typename T>
    Node<T>* create_tree(const std::vector<Connection<T>>& a)
    {
        if (a.empty()) return nullptr;

        std::unordered_map<T, Node<T>*> nodes;
        std::unordered_set<Node<T>*> children;

        for (const auto& con : a) {
            auto& dest = child_dest(get_node(nodes, con.parent), con.side);
            dest = get_node_as_new_child(nodes, children, con.child);
        }

        const auto root = nodes.at(a.front().parent);
        validate_root(root, children);
        return root;
    }

    // Recursively frees every node in a tree, nulling all pointers.
    // CAUTION: Huge branches will overflow the call stack.
    template<typename T>
    void destroy_tree(Node<T>*& root)
    {
        if (root != nullptr) {
            destroy_tree(root->left);
            destroy_tree(root->right);

            delete root;
            root = nullptr;
        }
    }
}

namespace { // path-returning iterative DFS implementation
    // Simulates continuations.
    enum class NextAction {
        check_null,
        compare_data,
        traverse_left_subtree,
        traverse_right_subtree, 
        pop_and_return
    };

    // Advances the state of the depth-first search. Returns false to halt the
    // search (either when the target is found or the stack is empty).
    template<typename T>
    inline bool advance_state(std::stack<NextAction>& actions,
                              std::stack<const Node<T>*>& path, const T& key)
    {
        if (actions.empty()) return false;

        switch (actions.top()) {
        case NextAction::check_null:
            actions.top() = (path.top() == nullptr ? NextAction::pop_and_return
                                                   : NextAction::compare_data);
            return true;

        case NextAction::compare_data:
            if (path.top()->data == key) return false;
            actions.top() = NextAction::traverse_left_subtree;
            return true;

        case NextAction::traverse_left_subtree:
            actions.top() = NextAction::traverse_right_subtree;
            actions.push(NextAction::check_null);
            path.push(path.top()->left);
            return true;

        case NextAction::traverse_right_subtree:
            actions.top() = NextAction::pop_and_return;
            actions.push(NextAction::check_null);
            path.push(path.top()->right);
            return true;

        case NextAction::pop_and_return:
            actions.pop();
            path.pop();
            return true;
        }

        throw std::invalid_argument{"corrupt state: invalid action on stack!"};
    }

    // Gets an std::stack of the path to the node with key as its data,
    // including the target node itself, or an empty stack if it is not found.
    // Implemented iteratively.
    template<typename T>
    std::stack<const Node<T>*> dfs(const Node<T>* root, const T& key)
    {
        std::stack<const Node<T>*> path;
        path.push(root);

        std::stack<NextAction> actions;
        actions.push(NextAction::check_null);

        while (advance_state(actions, path, key)) { }
        return path;
    }

    // Tests dfs() by printing the data associated with each node in the path,
    // from descendent to ancestor.
    template<typename T>
    void test_dfs(const Node<T>* root, const T& key)
    {
        std::cout << "[ ";

        for (auto path = dfs(root, key); !path.empty(); path.pop())
            std::cout << path.top()->data << ' ';

        std::cout << "]\n";
    }
}

int main()
{
    std::cout << "Please specify the tree by listing its connections.\n";
    auto root = create_tree(read_connections<int>());
    
    std::cout << "\nWhat key data do you want to find?\n";
    auto key = 0;
    std::cin >> key;

    std::cout << "\nKey-node to root path (empty if not found):\n";
    test_dfs(root, key);

    destroy_tree(root);
}
