// "Iterative" DFS that uses a stack of *just* the nodes traversed to arrive at
// the node being currently visited. When the target node is found, the stack
// is a path from the root to it; if the target node is not present, the stack
// is empty after the entire tree is traversed. Thus the stack is returned to
// the caller, indicating if the target is present, the identity of the target
// node, and the identity of all the nodes along the path that was found from
// the root to the target.

#include <iostream>
#include <memory>
#include <sstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>

namespace { // supporting types and functions
    enum class Side { left, right };

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

    template<typename T>
    struct Connection {
        T parent {}, child {};
        Side side {};
    };

    template<typename T>
    std::istream& operator>>(std::istream& in, Connection<T>& con)
    {
        return in >> con.parent >> con.child >> con.side;
    }

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

    template<typename T>
    struct Node {
        T data {};
        std::unique_ptr<Node> left {}, right {};
    };

    template<typename T>
    std::unique_ptr<Node<T>> make_tree(const std::vector<Connection<T>>& a)
    {
        std::unordered_set<std::unique_ptr
    }

}

int main()
{

}