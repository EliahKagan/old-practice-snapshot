#include <stdio.h>
#include <stdlib.h>

/*
 * This stores the total number of books in each shelf.
 */
int* total_number_of_books;

/*
 * This stores the total number of pages in each book of each shelf.
 * The rows represent the shelves and the columns represent the books.
 */
int** total_number_of_pages;

#include <assert.h>
#include <stdbool.h>

enum limits {
    min_number_of_shelves = 1,
    max_number_of_shelves = 100000,
    min_number_of_queries = 1,
    max_number_of_queries = 100000,
    min_type_of_query = 1,
    max_type_of_query = 3,
    min_number_of_books = 0,
    max_number_of_books = 1100
};

enum config {
    start_capacity = 8,
};

static_assert(__builtin_popcount(start_capacity) == 1,
              "the initial shelf capacity must be a power of 2");

static inline int (min)(const int x, const int y)
{
    return y < x ? y : x;
}

static inline void *xcalloc(const size_t count, const size_t size)
{
    void *const p = calloc(count, size);
    if (!p) abort();
    return p;
}

static inline void *xrealloc(void *const p, const size_t n)
{
    void *const q = realloc(p, n);
    if (!q) abort();
    return q;
}

static inline void require(const bool condition)
{
    if (!condition) abort();
}

static int read_total_number_of_shelves(void)
{
    int total_number_of_shelves = 0;
    (void)scanf("%d", &total_number_of_shelves);
    require(min_number_of_shelves <= total_number_of_shelves);
    require(total_number_of_shelves <= max_number_of_shelves);
    return total_number_of_shelves;
}

static int read_total_number_of_queries(void)
{
    int total_number_of_queries = 0;
    (void)scanf("%d", &total_number_of_queries);
    require(min_number_of_queries <= total_number_of_queries);
    require(total_number_of_queries <= max_number_of_queries);
    return total_number_of_queries;
}

static int read_type_of_query(void)
{
    int type_of_query = 0;
    (void)scanf("%d", &type_of_query);
    require(min_type_of_query <= type_of_query);
    require(type_of_query <= max_type_of_query);
    return type_of_query;
}

int main(void)
{
    const int total_number_of_shelves = read_total_number_of_shelves();

    total_number_of_books = xcalloc(total_number_of_shelves,
                                    sizeof *total_number_of_books);

    total_number_of_pages = xcalloc(total_number_of_shelves,
                                    sizeof *total_number_of_pages);

    int total_number_of_queries = read_total_number_of_queries();

    while (total_number_of_queries--) {
        const int type_of_query = read_type_of_query();

        if (type_of_query == 1) {
            int x = 0, y = 0;
            (void)scanf("%d %d", &x, &y);

            // Check that the shelf exists and is not full.
            require(0 <= x && x < total_number_of_shelves);
            assert(min_number_of_books <= total_number_of_books[x]);
            require(total_number_of_books[x] < max_number_of_books);

            enum { elem_size = sizeof *total_number_of_pages[x] };
            static_assert(elem_size == sizeof(int), "wrong element size");

            // If necessary, make room at the end of the shelf for the book.
            if (total_number_of_books[x] == 0) {
                assert(!total_number_of_pages[x]);
                total_number_of_pages[x] = xcalloc(start_capacity, elem_size);
            }
            else if (start_capacity <= total_number_of_books[x]
                     && __builtin_popcount(total_number_of_books[x]) == 1) {
                assert(total_number_of_pages[x]);

                const int capacity = (min)(total_number_of_books[x] * 2,
                                           max_number_of_books);

                total_number_of_pages[x] = xrealloc(total_number_of_pages[x],
                                                    capacity * elem_size);
            }

            // Place the book at the end of the shelf.
            assert(total_number_of_pages[x]);
            total_number_of_pages[x][total_number_of_books[x]++] = y;
        } else if (type_of_query == 2) {
            int x, y;
            scanf("%d %d", &x, &y);
            printf("%d\n", *(*(total_number_of_pages + x) + y));
        } else {
            int x;
            scanf("%d", &x);
            printf("%d\n", *(total_number_of_books + x));
        }
    }

    if (total_number_of_books) {
        free(total_number_of_books);
    }

    for (int i = 0; i < total_number_of_shelves; i++) {
        if (*(total_number_of_pages + i)) {
            free(*(total_number_of_pages + i));
        }
    }

    if (total_number_of_pages) {
        free(total_number_of_pages);
    }

    return 0;
}
