#include <regex.h>
#include <stdio.h>
#include <stdlib.h>

static void getln(char *const buf, const int buflen)
{
    if (fgets(buf, buflen, stdin) == NULL) abort();
}

static int getln_to_number(char *const buf, const int buflen)
{
    getln(buf, buflen);
    int ret = 0;
    if (sscanf(buf, "%d", &ret) != 1) abort();
    return ret;
}

int main(void)
{
    regex_t reg = { 0 };
    if (regcomp(&reg, "\\<\\w", 0) != 0) abort();
    
    enum { maxlen = 102 };
    char text[maxlen] = { 0 };
    
    for (int t = getln_to_number(text, maxlen); t > 0; --t) {
        getln(text, maxlen);
        
    }
}
