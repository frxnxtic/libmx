#include "../inc/libmx.h"

t_list *mx_create_node(void *data) {
    t_list *node = (t_list *)malloc(sizeof(t_list));
    if (node == NULL) {
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void mx_push_front(t_list **list, void *data) {
    t_list *node = mx_create_node(data);
    if (node == NULL) {
        return;
    }
    node->next = *list;
    *list = node;
}

void mx_push_back(t_list **list, void *data) {
    t_list *node = mx_create_node(data);
    if (node == NULL) {
        return;
    }
    if (*list == NULL) {
        *list = node;
        return;
    }
    t_list *last = *list;
    while (last->next != NULL) {
        last = last->next;
    }
    last->next = node;
}

void mx_pop_front(t_list **head) {
    if (*head == NULL) {
        return;
    }
    t_list *temp = (*head)->next;
    free(*head);
    *head = temp;
}

void mx_pop_back(t_list **head) {
    if (*head == NULL) {
        return;
    }
    if ((*head)->next == NULL) {
        free(*head);
        *head = NULL;
        return;
    }
    t_list *last = *head;
    while (last->next->next != NULL) {
        last = last->next;
    }
    free(last->next);
    last->next = NULL;
}

int mx_list_size(t_list *list) {
    int size = 0;
    for (t_list *node = list; node != NULL; node = node->next) {
        size++;
    }
    return size;
}

t_list *mx_sort_list(t_list *lst, bool (*cmp)(void *, void *)) {
    if (lst == NULL) {
        return NULL;
    }
    for (t_list *i = lst; i != NULL; i = i->next) {
        for (t_list *j = i->next; j != NULL; j = j->next) {
            if (cmp(i->data, j->data)) {
                void *temp = i->data;
                i->data = j->data;
                j->data = temp;
            }
        }
    }
    return lst;
}
