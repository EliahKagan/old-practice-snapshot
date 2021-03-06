/*You are required to complete below methods */

/*Inserts an entry with key x and value y in map */
void add_value(unordered_map<int,int> &m,int x,int y)
{
	m[x] = y;
}

/*Returns the value with key x from the map */
int find_value(unordered_map<int,int> &m,int x)
{
    const auto p = m.find(x);
    return p == m.end() ? -1 : p->second;
}

/*Returns the size of the map */
int getSize(unordered_map<int,int> &m)
{
    return m.size();
}

/*Removes the entry with key x from the map */
void removeKey(unordered_map<int,int> &m,int x)
{
    m.erase(x);
}