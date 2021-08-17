/*The function returns a vector containing the 
increasing sub-sequence of length 3 if present
else returns an empty vector */
vector<int> find3Numbers(const vector<int> seq, const int n)
{
    constexpr vector<int>::size_type len {3u};
    
    auto start = seq.cbegin();
    const auto stop = start + static_cast<vector<int>::difference_type>(n);
    
    while (start != stop) {
        vector<int> subseq {*start};
        for (auto cur = ++start; cur != stop; ++cur) {
            if (subseq.back() >= *cur) continue;
            subseq.push_back(*cur);
            if (subseq.size() == len) return subseq;
        }
    }
    
    return vector<int>{};
}
