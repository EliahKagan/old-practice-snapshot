#include <iostream>
using namespace std;

class Node {
public:
    Node *next;
    int data;
};

Node* insertIntoList(Node *cur, int data) {
    if(cur == nullptr) {
        cur = new Node();
        cur->data = data;
        cur->next = nullptr;
    }
    else {
        cur->next = insertIntoList(cur->next, data);
    }
    return cur;
}

long long getNumber(Node *head) {
    auto n = 0LL;
    for(; head != nullptr; head = head->next) {
        n <<= 1;
        n |= head->data;
    }
    return n;
}

int main()
{
    int N;
    cin >> N;
    Node *head = nullptr;

    for(int i = 0; i < (int)N; ++i) {
        int curData;
        cin >> curData;
        head = insertIntoList(head, curData);
    }

    cout << getNumber(head) << endl;

    return 0;
}
