/*
The structure to use is as follows
struct val{
	int first;
	int second;
};*/

/*You are required to complete this method*/
int maxChainLen(struct val *p, const int n)
{
    if (n == 0) return 0;

    const auto q = p + n;

    sort(p, q, [](const struct val& u, const struct val& v) {
        return u.second < v.second;
    });

    auto len = 1;

    for (auto cur = p->second; ++p != q; ) {
        if (cur < p->first) {
            cur = p->second;
            ++len;
        }
    }

    return len;
}
