/* A binary tree node has data, pointer to left child
   and a pointer to right child  
struct Node
{
    int data;
    Node* left;
    Node* right;
}; */

namespace {
    enum class Side { top, left, right };
    
    inline void add(vector<int> &a, const int parent_index,
                    const int child_data, const Side side)
    {
        a.push_back(parent_index);
        a.push_back(child_data);
        a.push_back(static_cast<int>(side));
    }
    
    void grow(vector<int> &, int, Node *, Side);
    
    void grow_children(vector<int> &a, Node *const node)
    {
        const auto parent_index = a.size() - 1;
        grow(a, parent_index, node->left, Side::left);
        grow(a, parent_index, node->right, Side::right);
    }
    
    void grow(vector<int> &a, const int parent_index,
              Node *const node, const Side side)
    {
        if (node != nullptr) {
            add(a, parent_index, node->data, side);
            grow_children(a, node);
        }
    }
}

/*this  function serializes 
the binary tree and stores 
it in the vector A*/
void serialize(Node *const root, vector<int> &a)
{
    grow(a, -1, root, Side::top);
    
    constexpr static array<char, 3> sides {'T', 'L', 'R'};
    
    assert(a.size() % 3 == 0);
    for (auto i = 0; i != a.size(); i += 3) {
        std::cout << a[i]                       // parent index
                  << ' ' << i / 3               // child index
                  << " (" << a[i + 1] << ") "   // child data
                  << sides[a[i + 2]] << '\n';   // side
    }
}

/*this function deserializes
 the serialized vector A*/
Node * deSerialize(vector<int> &A)
{
    return nullptr; // FIXME: implement this
}
