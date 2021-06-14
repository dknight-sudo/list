#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "mergesort.c"

static bool validate(struct list_head *list)
{
    struct list_head *node;
    list_for_each(node, list)
    {
        if (node->next == list)
            break;
        if (strcmp(list_entry(node, list_ele_t, list)->value,
                   list_entry(node->next, list_ele_t, list)->value) > 0)
            return false;
    }
    return true;
}

void list_free(struct list_head *list)
{
    if(list_empty(list))
        return;
    struct list_head *node, *tmp;
    list_for_each_safe(node, tmp, list)
    {
        list_del(node);
        free(list_entry(node, list_ele_t, list));
    }
    
}


bool ele_insert_head(struct list_head *head,char *s)
{
    if ( !head)
        return false;
    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (!newh)
        return false;
    char *new_value = strdup(s);
    if (!new_value){
        free(newh);
        return false;
    }
    newh->value = new_value;
    list_add_tail(&newh->list, head);
    return true;
}

int main(void)
{
    FILE *fp = fopen("cities.txt", "r");
    if (!fp) {
        perror("failed to open cities.txt");
        exit(EXIT_FAILURE);
    }

    struct list_head head;
    INIT_LIST_HEAD(&head);
    struct list_head cur = head;
    char buf[256];
    while (fgets(buf, 256, fp))
        ele_insert_head(&head, buf);
    fclose(fp);

    list_merge_sort(&head);
    assert(validate(&head));

    list_free(&head);

    return 0;
}