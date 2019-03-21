/*
 * Code for basic C skills diagnostic.
 * Developed for courses 15-213/18-213/15-513 by R. E. Bryant, 2017
 * Modified to store strings, 2018
 */

/*
 * This program implements a queue supporting both FIFO and LIFO
 * operations.
 *
 * It uses a singly-linked list to represent the set of queue elements
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "harness.h"
#include "queue.h"

/*
  Create empty queue.
  Return NULL if could not allocate space.
*/
queue_t *q_new()
{
    queue_t *q = malloc(sizeof(queue_t));

    if (q == NULL) {
        return NULL;
    }

    q->head = NULL;
    q->tail = NULL;
    q->q_size = 0;
    return q;
}

/* Free all storage used by queue */
void q_free(queue_t *q)
{
    if (q == NULL) {
        return;
    }

    while (q->head) {
        list_ele_t *tmp = q->head->next;
        free(q->head->value);
        free(q->head);
        q->head = tmp;
    }

    free(q);
}

/*
  Attempt to insert element at head of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_head(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newh = malloc(sizeof(list_ele_t));
    if (newh == NULL) {
        return false;
    }

    newh->value = malloc(strlen(s) + sizeof(char));
    if (newh->value == NULL) {
        free(newh);
        return false;
    }
    strcpy(newh->value, s);

    if (q->tail == NULL) {
        q->tail = newh;
    }
    newh->next = q->head;
    q->head = newh;
    q->q_size++;

    return true;
}


/*
  Attempt to insert element at tail of queue.
  Return true if successful.
  Return false if q is NULL or could not allocate space.
  Argument s points to the string to be stored.
  The function must explicitly allocate space and copy the string into it.
 */
bool q_insert_tail(queue_t *q, char *s)
{
    if (q == NULL) {
        return false;
    }

    list_ele_t *newt = malloc(sizeof(list_ele_t));
    if (newt == NULL) {
        return false;
    }
    newt->next = NULL;
    newt->value = malloc(strlen(s) + sizeof(char));
    if (newt->value == NULL) {
        free(newt);
        return false;
    }
    strcpy(newt->value, s);

    if (q->head == NULL) {
        q->head = newt;
    }

    if (q->tail != NULL) {
        q->tail->next = newt;
    }

    q->tail = newt;
    q->q_size++;

    return true;
}

/*
  Attempt to remove element from head of queue.
  Return true if successful.
  Return false if queue is NULL or empty.
  If sp is non-NULL and an element is removed, copy the removed string to *sp
  (up to a maximum of bufsize-1 characters, plus a null terminator.)
  The space used by the list element and the string should be freed.
*/
bool q_remove_head(queue_t *q, char *sp, size_t bufsize)
{
    if (q == NULL || q->q_size == 0) {
        return false;
    }

    list_ele_t *oldh = q->head;

    if (sp != NULL && bufsize) {
        *sp = '\0';
        strncat(sp, oldh->value, bufsize - 1);
    }

    if (q->tail == oldh) {
        q->tail = NULL;
    }
    q->head = q->head->next;
    q->q_size--;
    free(oldh->value);
    free(oldh);

    return true;
}

/*
  Return number of elements in queue.
  Return 0 if q is NULL or empty
 */
int q_size(queue_t *q)
{
    return q == NULL ? 0 : q->q_size;
}

/*
  Reverse elements in queue
  No effect if q is NULL or empty
  This function should not allocate or free any list elements
  (e.g., by calling q_insert_head, q_insert_tail, or q_remove_head).
  It should rearrange the existing ones.
 */
void q_reverse(queue_t *q)
{
    if (q == NULL || q->q_size == 0 || q->head == NULL) {
        return;
    }

    q->tail = q->head;

    list_ele_t *prev = NULL;
    list_ele_t *cur = q->head;
    list_ele_t *next;
    while (cur != NULL) {
        next = cur->next;
        cur->next = prev;
        prev = cur;
        cur = next;
    }

    q->head = prev;
}
