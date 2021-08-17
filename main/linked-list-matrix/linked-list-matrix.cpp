/*Please note that it's Function problem i.e.
you need to write your solution in the form of Function(s) only.
Driver Code to call/invoke your function is mentioned above.*/

/*structure of the node of the linked list is as
struct Node
{
	int data;
	Node* right, *down;
};*/
// n is the size of the matrix
// function must return the pointer to the first element
// of the in linked list i.e. that should be the element at arr[0][0]
Node* constructLinkedMatrix(int mat[MAX][MAX], int n)
{
    assert(n >= 0);

    vector<Node*> row (n + 1);

    for (auto i = n; i-- != 0; ) {
        for (auto j = n; j-- != 0; )
            row[j] = new Node{mat[i][j], row[j + 1], row[j]};
    }

    return row.front();
}
