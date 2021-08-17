/*You are required to complete this method */
bool isInterleave(const string a, const string b, const string c) 
{
    if (a.size() + b.size() != c.size()) return false;
    
    using It = string::const_iterator;
    const auto pp = a.cend(), qq = b.cend(), rr = c.cend();
    
    const function<bool(It, It, It)>
    dfs {[pp, qq, rr, &dfs](const It p, const It q, const It r) {
        return r == rr || (p != pp && *p == *r && dfs(next(p), q, next(r)))
                       || (q != qq && *q == *r && dfs(p, next(q), next(r)));
    }};
    
    return dfs(a.cbegin(), b.cbegin(), c.cbegin());
}
