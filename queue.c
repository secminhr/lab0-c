#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
 * Create empty queue.
 * Return NULL if could not allocate space.
 */
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));
    if (q != NULL) {
        q->head = NULL;
        q->tail = NULL;
        q->size = 0;
    }
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }
    /* Free all list elements and strings */
    while (q->head) {
        list_ele_t *tmp = q->head;
        q->head = q->head->next;
        free(tmp->value);
        free(tmp);
    }
    /* Free queue structure */
    free(q);
}

/*
 * Attemp to allocate an element.
 * Return NULL if q is NULL or allocation failed,
 * Return newly allocated element otherwise.
 */
static list_ele_t *alloc_ele(queue_t *q, size_t value_size)
{
    if (q == NULL) {
        return NULL;
    }
    list_ele_t *new = malloc(sizeof(list_ele_t));
    if (new == NULL) {
        return NULL;
    }
    char *value = malloc(value_size);
    if (value == NULL) {
        free(new);
        return NULL;
    }
    new->value = value;
    return new;
}

/*
 * Attempt to insert element at head of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    list_ele_t *newh = alloc_ele(q, strlen(s) + 1);
    if (newh == NULL) {
        return false;
    }
    strncpy(newh->value, s, strlen(s) + 1);
    newh->next = q->head;
    q->head = newh;
    if (q->size == 0) {
        q->tail = newh;
    }
    q->size++;
    return true;
}

/*
 * Attempt to insert element at tail of queue.
 * Return true if successful.
 * Return false if q is NULL or could not allocate space.
 * Argument s points to the string to be stored.
 * The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    list_ele_t *newt = alloc_ele(q, strlen(s) + 1);
    if (newt == NULL) {
        return false;
    }
    strncpy(newt->value, s, strlen(s) + 1);
    newt->next = NULL;
    if (q->size) {
        q->tail->next = newt;
    } else {
        q->head = newt;
    }
    q->tail = newt;
    q->size++;
    return true;
}

/*
 * Attempt to remove element from head of queue.
 * Return true if successful.
 * Return false if queue is NULL or empty.
 * If sp is non-NULL and an element is removed, copy the removed string to *sp
 * (up to a maximum of bufsize-1 characters, plus a null terminator.)
 * The space used by the list element and the string should be freed.
 */
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->size == 0) {
        return false;
    }
    list_ele_t *old_head = q->head;
    q->head = q->head->next;
    if (q->size == 1) {
        q->tail = NULL;
    }
    q->size--;
    if (sp != NULL) {
        strncpy(sp, old_head->value, bufsize - 1);
        *(sp + bufsize - 1) = '\0';
    }
    free(old_head->value);
    free(old_head);
    return true;
}

/*
 * Return number of elements in queue.
 * Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q == NULL ? 0 : q->size;
}

/*
 * Reverse elements in queue
 * No effect if q is NULL or empty
 * This function should not allocate or free any list elements
 * (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
 * It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->size == 0) {
        return;
    }
    list_ele_t *prev = NULL;
    list_ele_t *cur = q->head;
    while (cur) {
        list_ele_t *next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    q->tail = q->head;
    q->head = prev;
}

/*
 * Sort elements of queue in ascending order
 * No effect if q is NULL or empty. In addition, if q has only one
 * element, do nothing.
 */
void q_sort(queue_t *q)
{
    /* TODO: You need to write the code for this function */
    /* TODO: Remove the above comment when you are about to implement. */
}
