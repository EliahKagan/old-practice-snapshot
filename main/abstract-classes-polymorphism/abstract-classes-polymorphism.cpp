#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <set>
#include <cassert>
using namespace std;

struct Node {
    Node* next;
    Node* prev;
    int value;
    int key;
    Node(Node* p, Node* n, int k, int val) :prev(p), next(n), key(k), value(val) {};
    Node(int k, int val) :prev(NULL), next(NULL), key(k), value(val) {};
};

class Cache {

protected:
    map<int, Node*> mp; //map the key to the node in the linked list
    int cp;  //capacity
    Node* tail; // double linked list tail pointer
    Node* head; // double linked list head pointer
    virtual void set(int, int) = 0; //set function
    virtual int get(int) = 0; //get function

};

// This version fixes a subtle, serious bug where reused nodes had only their
// external (map) keys changed, and not their internal key fields. The
// HackerRank unit tests did not find this bug.
class LRUCache : public Cache {
public:
    explicit LRUCache(const int capacity)
    {
        assert(capacity > 0);
        cp = capacity;
        head = tail = nullptr;
    }
    
    explicit LRUCache(const LRUCache&) = delete;
    explicit LRUCache(LRUCache&&) = delete;
    
    LRUCache& operator=(const LRUCache&) = delete;
    LRUCache& operator=(LRUCache&&) = delete;
    
    virtual ~LRUCache();
    
    void set(int key, int value) override;
    int get(int key) override;
    
    static constexpr int element_not_found() { return -1; }
    
private:
    void move_to_head(Node* node);
    
    void assign_and_move_to_head(Node* const node, const int value)
    {
        node->value = value;
        move_to_head(node);
    }
    
    void assign_and_move_to_head(Node* const node,
                                 const int key, const int value)
    {
        node->key = key;
        assign_and_move_to_head(node, value);
    }
};

LRUCache::~LRUCache()
{
    for (; head != nullptr; head = head->next) delete head->prev;
    delete tail;
}

void LRUCache::set(const int key, const int value)
{
    const auto entp = mp.find(key);
    
    if (entp != mp.end()) {
        assign_and_move_to_head(entp->second, value);
        return;
    }
    
    if (mp.empty()) head = tail = new Node(key, value);
    else if (static_cast<int>(mp.size()) < cp) {
        head->prev = new Node(nullptr, head, key, value);
        head = head->prev;
    } else {
        mp.erase(tail->key);
        assign_and_move_to_head(tail, key, value);
    }
    
    mp.emplace(key, head);
}

int LRUCache::get(int key)
{
    const auto entp = mp.find(key);
    
    if (entp == mp.end()) return element_not_found();
    
    move_to_head(entp->second);
    return head->value;
}

void LRUCache::move_to_head(Node* const node)
{
    if (node->prev == nullptr) return; // already at head
    
    // remove node from its current position in the list
    node->prev->next = node->next;
    (node->next == nullptr ? tail : node->next->prev) = node->prev;
    
    // re-add node at the head of the list
    node->prev = nullptr;
    node->next = head;
    head->prev = node;
    head = node;
}

int main() {
    int n, capacity, i;
    cin >> n >> capacity;
    LRUCache l(capacity);
    for (i = 0; i<n; i++) {
        string command;
        cin >> command;
        if (command == "get") {
            int key;
            cin >> key;
            cout << l.get(key) << endl;
        }
        else if (command == "set") {
            int key, value;
            cin >> key >> value;
            l.set(key, value);
        }
    }
    return 0;
}
