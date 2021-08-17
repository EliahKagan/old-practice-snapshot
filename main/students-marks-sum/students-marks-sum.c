#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <assert.h>

int marks_summation(const int* const marks, const int number_of_students,
                    const char gender)
{
    assert(gender == 'b' || gender == 'g');

    int acc = 0;
    for (int i = gender == 'g'; i < number_of_students; i += 2)
        acc += marks[i];

    return acc;
}

int main() {
    int number_of_students;
    char gender;
    int sum;

    scanf("%d", &number_of_students);
    int *marks = (int *) malloc(number_of_students * sizeof (int));

    for (int student = 0; student < number_of_students; student++) {
        scanf("%d", (marks + student));
    }

    scanf(" %c", &gender);
    sum = marks_summation(marks, number_of_students, gender);
    printf("%d", sum);
    free(marks);

    return 0;
}
