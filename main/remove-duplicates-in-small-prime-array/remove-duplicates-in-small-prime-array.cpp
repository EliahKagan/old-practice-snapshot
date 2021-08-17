/*you need to complete this function*/
void removeDuplicate(vector<int> &vect)
{
    vector<int> uniq;
    uniq.reserve(vect.size());

    set<int> memo;
    for (const auto elem : vect) {
        if (memo.find(elem) == memo.end()) {
            memo.insert(elem);
            uniq.push_back(elem);
        }
    }

    uniq.shrink_to_fit();
    uniq.swap(vect);
}
