static char *strcpy(char *const dest, const char *src)
{
    for (char *p = dest; (*p++ = *src++) != '\0'; ) { }
    return dest;
}

int main(void) // unit test for strcpy()
{
    void abort(void);
    int printf(const char *restrict fmt, ...);
    
    const char src[] = "Hello, world!";
    char dest[sizeof src] = { 0 };
    
    char *const ret = strcpy(dest, src);
    if (ret != dest) abort();
    
    printf("%s\n", dest);
}
