#include <errno.h>
#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdnoreturn.h>
#include <string.h>

static const char *g_progname;

#ifdef __GNUC__
__attribute__ ((format(printf, 1, 2)))
#endif
static noreturn void die(const char *restrict const format, ...)
{
    fprintf(stderr, "%s: error: ", g_progname);
    
    va_list args;
    va_start(args, format);
    vfprintf(stderr, format, args);
    va_end(args);
    
    fputc('\n', stderr);
    
    exit(EXIT_FAILURE);
}

static noreturn void iodie(const char *restrict const action,
                           const char *restrict const path)
{
    if (errno == 0) die("can't %s %s", action, path);
    else die("can't %s %s: %s", action, path, strerror(errno));
}

static void seed_generator()
{
    const char* const path = "/dev/random";
    
    errno = 0; // not strictly necessary in this case
    FILE *device = fopen(path, "rb");
    if (device == NULL) iodie("open", path);
    
    unsigned seed = 0u;
    
    errno = 0;
    if (fread(&seed, sizeof seed, 1u, device) != 1) iodie("read", path);
    
    errno = 0;
    if (fclose(device) != 0) iodie("close", path);
    
    srand(seed);
}

static unsigned random_in_range(const unsigned upper_inclusive)
{
    const unsigned upper = upper_inclusive + 1u;
    
    unsigned cutoff = (unsigned)RAND_MAX + 1u;
    cutoff -= cutoff % upper;
    
    unsigned r;
    do r = (unsigned)rand();
    while (r >= cutoff);
    
    return r % upper;
}

static unsigned random_power_of_2(void)
{
    const unsigned max_shift = 30;
    return 1u << random_in_range(max_shift);
}

int main(int argc, char **argv)
{
    (void)argc;
    g_progname = argv[0];
    
    seed_generator();
    
    for (int i = 1; i <= 20; ++i)
        printf("Run %2d:  %u\n", i, random_power_of_2());
    
    return EXIT_SUCCESS;
}
