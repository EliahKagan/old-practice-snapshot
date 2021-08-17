/* Structure of Node used
struct Node
{
    int coeff;  // coefficient of the polynomial 
    int pow;   // power of the polynomial 
    Node* next;
};
*/

namespace {
    void combineLikeTerms(map<int, int>& acc, const Node* head)
    {
        for (; head != nullptr; head = head->next)
            acc[head->pow] += head->coeff;
    }
    
    void printTerms(const map<int, int>& terms)
    {
        auto sep = "";
        
        for_each(terms.crbegin(), terms.crend(),
                 [&sep](const pair<int, int>& pow_coeff) {
            if (pow_coeff.second != 0) {
                cout << sep << pow_coeff.second << "x^" << pow_coeff.first;
                sep = " + ";
            }
        });
    }
}

/* The below method print the required sum of polynomial
p1 and p2 as specified in output  */
void addPolynomial(Node *const p1, Node *const p2)
{
    map<int, int> terms;
    combineLikeTerms(terms, p1);
    combineLikeTerms(terms, p2);
    
    printTerms(terms);
}
