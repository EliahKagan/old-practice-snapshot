void reverse(char *str, int len)
{
    stack<char> s;
    
    for (auto i = 0; i != len; ++i) s.push(str[i]);
    
    for (auto i = 0; i != len; ++i) {
        str[i] = s.top();
        s.pop();
    }
}
