class Solution {
public:
    static vector<int> intersect(const vector<int>& a,
                                    const vector<int>& b);

private:
    static void intersect(const vector<int>& a, const vector<int>& b,
                          back_insert_iterator<vector<int>> it);
};

vector<int> Solution::intersect(const vector<int>& a, const vector<int>& b)
{
    vector<int> ret;

    if (a.size() > b.size()) {
        intersect(b, a, back_inserter(ret));
    } else {
        intersect(a, b, back_inserter(ret));
    }

    return ret;
}

void Solution::intersect(const vector<int>& a, const vector<int>& b,
                         back_insert_iterator<vector<int>> it)
{
    unordered_multiset<int> xs (cbegin(a), cend(a));

    copy_if(cbegin(b), cend(b), it, [&xs](const int y) {
        const auto p = xs.find(y);
        if (p == cend(xs)) return false;
        xs.erase(p);
        return true;
    });
}
