#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING_LENGTH 6

struct package {
	char* id;
	int weight;
};

typedef struct package package;

struct post_office {
	int min_weight;
	int max_weight;
	package* packages;
	int packages_count;
};

typedef struct post_office post_office;

struct town {
	char* name;
	post_office* offices;
	int offices_count;
};

typedef struct town town;

static void *xmalloc(const size_t n)
{
    void *const ret = malloc(n);
    if (!ret) abort();
    return ret;
}

static void *xrealloc(void *const ptr, const size_t n)
{
    void *const ret = realloc(ptr, n);
    if (!ret) abort();
    return ret;
}

void print_all_packages(const town *const t)
{
    printf("%s:\n", t->name);
    for (int i = 0; i < t->offices_count; ++i) {
        printf("\t%d:\n", i);
        for (int j = 0; j < t->offices[i].packages_count; ++j)
            printf("\t\t%s\n", t->offices[i].packages[j].id);
    }
}

static void move_acceptable_packages(post_office *const src,
                                     post_office *const dest)
{
    const int min_weight = dest->min_weight, max_weight = dest->max_weight;

    int delta = 0;
    for (int i = 0; i < src->packages_count; ++i) {
        const int weight = src->packages[i].weight;
        if (min_weight <= weight && weight <= max_weight) ++delta;
    }

    const int new_dest_count = dest->packages_count + delta;
    dest->packages = xrealloc(dest->packages,
                              new_dest_count * sizeof *dest->packages);

    int left = 0;
    for (int right = 0; right < src->packages_count; ++right) {
        const int weight = src->packages[right].weight;
        if (min_weight <= weight && weight <= max_weight)
            dest->packages[dest->packages_count++] = src->packages[right];
        else
            src->packages[left++] = src->packages[right];
    }

    assert(dest->packages_count == new_dest_count);
    assert(left = src->packages_count - delta);
    src->packages_count = left;
}

void send_all_acceptable_packages(
        town *const source, const int source_office_index,
        town *const target, const int target_office_index)
{
    assert(0 <= source_office_index);
    assert(source_office_index < source->offices_count);
    post_office *const src = source->offices + source_office_index;

    assert(0 <= target_office_index);
    assert(target_office_index < target->offices_count);
    post_office *const dest = target->offices + target_office_index;

    move_acceptable_packages(src, dest);
}

static int count_packages(const town *const t)
{
    assert(t);

    int count = 0;
    for (int i = 0; i < t->offices_count; ++i)
        count += t->offices[i].packages_count;

    return count;
}

town* town_with_most_packages(town* towns, int towns_count)
{
    assert(towns_count > 0);
    town *best_town = towns++;
    int best_count = count_packages(best_town);

    while (--towns_count > 0) {
        const int count = count_packages(towns);

        if (best_count < count) {
            best_count = count;
            best_town = towns;
        }

        ++towns;
    }

    return best_town;
}

town* find_town(town* towns, int towns_count, const char* const name)
{
    assert(name);

    while (towns_count-- > 0) {
        assert(towns);
        assert(towns->name);
        if (strcmp(towns->name, name) == 0) return towns;
        ++towns;
    }

    abort();
}

int main(void)
{
	int towns_count;
	scanf("%d", &towns_count);
	town* towns = xmalloc(sizeof(town)*towns_count);
	for (int i = 0; i < towns_count; i++) {
		towns[i].name = xmalloc(sizeof(char) * MAX_STRING_LENGTH);
		scanf("%s", towns[i].name);
		scanf("%d", &towns[i].offices_count);
		towns[i].offices = xmalloc(sizeof(post_office)*towns[i].offices_count);
		for (int j = 0; j < towns[i].offices_count; j++) {
			scanf("%d%d%d", &towns[i].offices[j].packages_count, &towns[i].offices[j].min_weight, &towns[i].offices[j].max_weight);
			towns[i].offices[j].packages = xmalloc(sizeof(package)*towns[i].offices[j].packages_count);
			for (int k = 0; k < towns[i].offices[j].packages_count; k++) {
				towns[i].offices[j].packages[k].id = xmalloc(sizeof(char) * MAX_STRING_LENGTH);
				scanf("%s", towns[i].offices[j].packages[k].id);
				scanf("%d", &towns[i].offices[j].packages[k].weight);
			}
		}
	}
	int queries;
	scanf("%d", &queries);
	char town_name[MAX_STRING_LENGTH];
	while (queries--) {
		int type;
		scanf("%d", &type);
		switch (type) {
		case 1:
			scanf("%s", town_name);
			town* t = find_town(towns, towns_count, town_name);
			print_all_packages(t);
			break;
		case 2:
			scanf("%s", town_name);
			town* source = find_town(towns, towns_count, town_name);
			int source_index;
			scanf("%d", &source_index);
			scanf("%s", town_name);
			town* target = find_town(towns, towns_count, town_name);
			int target_index;
			scanf("%d", &target_index);
			send_all_acceptable_packages(source, source_index, target, target_index);
			break;
		case 3:
			printf("Town with the most number of packages is %s\n", town_with_most_packages(towns, towns_count)->name);
			break;
		}
	}
	return 0;
}
