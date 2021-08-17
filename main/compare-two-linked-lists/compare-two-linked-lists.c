// Compare two strings represented as linked lists
int compare(struct Node *list1, struct Node *list2) 
{
    for (; ; list1 = list1->next, list2 = list2->next) {
        if (list1 == NULL) return list2 == NULL ? 0 : -1;
        if (list2 == NULL) return 1;
        if (list1->c < list2->c) return -1;
        if (list1->c > list2->c) return 1;
    }
}
