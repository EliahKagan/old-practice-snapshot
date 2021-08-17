// function to calculate minimum numbers of characters
// to be removed to make two strings anagram
int remAnagram(string str1, string str2)
{
    unordered_map<char, int> diffs;
    for (const auto c : str1) ++diffs[c];
    for (const auto c : str2) --diffs[c];
    
    int acc = 0;
    for (const auto& kv : diffs) acc += abs(kv.second);
    return acc;
}
