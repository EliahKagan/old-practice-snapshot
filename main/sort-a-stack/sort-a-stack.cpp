/*The structure of the class is
class SortedStack{
public:
	stack<int> s;
	void sort();
};
*/

/* The below method sorts the stack s 
you are required to complete the below method */
void SortedStack::sort()
{
    vector<int> a;
    for (a.reserve(s.size()); !s.empty(); s.pop()) a.push_back(s.top());
    
    std::sort(begin(a), end(a));
    for (const auto x : a) s.push(x);
}
