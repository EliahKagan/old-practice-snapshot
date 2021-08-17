/* Below global variable is declared in code for modulo arithmetic
const long long unsigned int MOD = 1000000007; */

/* Link list Node/
struct Node
{
    bool data;   // NOTE data is bool
    struct Node* next;
}; */

// Should return decimal equivalent modulo 1000000007 of binary linked list 
long long unsigned int decimalValue(struct Node *head)
{
    constexpr __int128 mod {1000000007};
    
    __int128 n {0};
    
    for (; head != nullptr; head = head->next) {
        n <<= 1;
        n |= static_cast<__int128>(head->data);
    }
    
    return static_cast<long long>(n % mod);
}
