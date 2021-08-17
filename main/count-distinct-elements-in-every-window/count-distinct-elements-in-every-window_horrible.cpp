/*You are required to complete below method */
void countDistinct(int *const a, const int k, const int n)
{
    unordered_set<int> distinct;
    unordered_multiset<int> all;
    
    auto t = 0;
    for (cin >> t; t > 0; --t) {
        distinct.clear();
        all.clear();
        queue<int> q;
        
        auto n = 0, k = 0;
        cin >> n >> k;
        
        for (n -= k; k > 0; --k) {
            auto x = 0;
            cin >> x;
            distinct.insert(x);
            all.insert(x);
            q.push(x);
        }
        
        for (cout << distinct.size(); n-- > 0; cout << ' ' << distinct.size()) {
            all.erase(all.find(q.front())); // remove just one
            if (all.find(q.front()) == all.cend()) distinct.erase(q.front());
            q.pop();
            
            auto x = 0;
            cin >> x;
            distinct.insert(x);
            all.insert(x);
            q.push(x);
        }
        
        cout << '\n';
    }
}
