/* You are required to complete below methods */

/*inserts an element x to the set s */
void insert(set<int> &s,int x)
{
    s.insert(x);
}

/*prints the contents of the set s */
void print_contents(set<int> &s)
{
    for (const auto x : s) cout << x << ' ';
    //cout << '\n';
}

/*erases an element x from the set s */
void erase(set<int> &s,int x)
{
    s.erase(x);
}

/*returns 1 if the element x is
present in set s else returns -1 */
int find(set<int> &s,int x)
{
    return s.find(x) == s.end() ? -1 : 1;
}

/*returns the size of the set s */
int size(set<int> &s)
{
    return s.size();
}
