// C program to find n'th Node in linked list
#include <stdio.h>
#include <stdlib.h>
#include<iostream>
using namespace std;

/* Link list Node */
struct Node
{
    int data;
    struct Node* next;
};

void append(struct Node** head_ref, struct Node **tail_ref,
            int new_data)
{
    struct Node* new_node = new Node;
    new_node->data  = new_data;
    new_node->next = NULL;
    if (*head_ref == NULL)
        *head_ref = new_node;
    else
        (*tail_ref)->next = new_node;
    *tail_ref = new_node;
}

/* Function to get the middle of the linked list*/
int maxPalindrome(Node *);



/* Driver program to test above function*/
int main()
{
    int T,n,l;
    cin>>T;

    while(T--)
    {
        struct Node *head = NULL,  *tail = NULL;

        cin>>n;
        for (int i=1; i<=n; i++)
        {
            cin>>l;
            append(&head, &tail, l);
        }
      

       cout << maxPalindrome(head)<<endl;
    }
    return 0;
}


/* The Node is defined 
  struct Node
  {
     int data;
     Node *next;
  } */

namespace {
    // Offset is ptdiff_t, which I'm not using as I shouldn't include <cstddef>
    // as "using namespace std;" at file scope shouldn't precede an "#include".
    using Offset = decltype(static_cast<int *>(nullptr)
                            - static_cast<int *>(nullptr));

    // Copies the numbers from the list beginning at head to the array, dest,
    // but stops before writing to *endp. Returns a past-the-end pointer.
    int *copyToArray(int *dest, int *const endp, const Node *head)
    {
        for (; head != nullptr && dest != endp; head = head->next)
            *dest++ = head->data;

        return dest;
    }

    // Checks if [first, last) is a palindrome.
    inline bool isPalindrome(const int *first, const int *last)
    {
        while (first < last)
            if (*first++ != *--last) return false;

        return true;
    }

    // Checks if the window [first, mid), or any window that may be obtained by
    // sliding it to the right such that its width remains the same and
    // mid <= right, is a palindrome.
    inline bool windowSlidesToPalindrome(const int *first, const int *mid,
                                         const int *const last)
    {
        for (; ; ++first, ++mid) {
            if (isPalindrome(first, mid)) return true;
            if (mid == last) return false;
        }
    }

    // Finds the length of the longest palindrome in [first, last).
    Offset findMaxPalindromeLength(const int *const first,
                                   const int *const last)
    {
        auto mid = last;

        while (mid != first && !windowSlidesToPalindrome(first, mid, last))
            --mid;

        return mid - first;
    }
}

/*The function below returns an int denoting
the length of the longest palindrome list. */
int maxPalindrome(Node *const head)
{
    static constexpr Offset maxlen {1024};
    
    int a[1024] {};
    const auto last = copyToArray(a, a + maxlen, head);

    return static_cast<int>(findMaxPalindromeLength(a, last));
}
