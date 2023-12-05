#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct dlnode
{
    int data;
    struct dlnode *next;
    struct dlnode *prev;
} dlnode;

typedef struct ndlst
{
    dlnode *head; // points to the first element otherwise NULL
    dlnode *tail; // points to the last element otherwise NULL
    int len;      // number of elements
} ndlst;

// Pre: None
// Post: Creates a null list
ndlst *dlistCreate(void)
{
    ndlst *ret = malloc(sizeof(ndlst));
    ret->head = NULL;
    ret->tail = NULL;
    ret->len = 0;
    return ret;
}

// Pre: lst is a valid list ( even null )
// Post: Destroys the list
void dlistDestroy(ndlst *lst)
{
    dlnode *next_node = lst->head;
    dlnode *curr_node = NULL;
    while (next_node)
    {
        curr_node = next_node;
        next_node = next_node->next;
        free(curr_node);
    }
    free(lst);
}

// Pre: lst is valid
// Post: returns the number of elements in the list
int dlistLength(ndlst *lst)
{
    return lst->len;
}

// Pre: lst is a valid list with length of at least n
// Post: nth item removed
void dlistRemoveElem(ndlst *lst, int n)
{
    lst->len--;

    if (n == 1)
    {
        dlnode *new_head = lst->head->next;
        free(lst->head);
        lst->head = new_head;
        if (lst->head)
        {
            lst->head->prev = NULL;
        }
        else
        {
            lst->tail = NULL;
        }
        return;
    }

    dlnode *next_node = lst->head;
    for (int i = 1; i < n - 1; i++)
    {
        next_node = next_node->next;
    }

    if (next_node->next->next == NULL)
    {
        free(lst->tail);
        next_node->next = NULL;
        lst->tail = next_node;
        return;
    }

    dlnode *tmp = next_node->next;
    next_node->next = next_node->next->next;
    next_node->next->prev = next_node;
    free(tmp);
}
// lst is a valid list
void dlistAddToFront(ndlst *lst, int elem)
{
    lst->len++;
    dlnode *new_node = malloc(sizeof(dlnode));
    new_node->data = elem;
    new_node->prev = NULL;

    if (lst->head == NULL)
    {
        new_node->next = NULL;
        lst->head = new_node;
        lst->tail = new_node;
        return;
    }

    new_node->next = lst->head;
    lst->head->prev = new_node;
    lst->head = new_node;
}

// lst is a valid list
void dlistAddToEnd(ndlst *lst, int elem)
{
    lst->len++;
    dlnode *new_node = malloc(sizeof(dlnode));
    new_node->data = elem;
    new_node->next = NULL;

    if (lst->head == NULL)
    {
        new_node->prev = NULL;
        lst->head = new_node;
        lst->tail = new_node;
        return;
    }

    new_node->prev = lst->tail;
    lst->tail->next = new_node;
    lst->tail = new_node;
}

// Pre: lst is valid
// prints the items in the list from start to end.
void dlistPrint(ndlst *lst)
{
    dlnode *node = lst->head;
    // iterate over the nodes (items) until node is NULL
    // and print the data
    for (; node; node = node->next)
        printf("%d  ", node->data);
    printf("\n");
}

void dlistPrintReverse(ndlst *lst)
{
    dlnode *node = lst->tail;
    // iterate over the nodes (items) until node is NULL
    // and print the data
    for (; node; node = node->prev)
        printf("%d  ", node->data);
    printf("\n");
}

void dlistSort(ndlst *lst)
{
    // bubble sort
    if (lst->len <= 1)
    {
        return;
    }

    for (dlnode *i = lst->head; i->next; i = i->next)
    {
        int flag = 1;
        for (dlnode *j = lst->head; j->next->next; j = j->next)
        {
            if (j->data > j->next->data)
            {
                // swaps data
                int tmp = j->data;
                j->data = j->next->data;
                j->next->data = tmp;
                flag = 0;
            }
        }
        if (flag)
        {
            break;
        }
    }
}

// rotate the list n times to the left, assume, list not empty
void dlistRotateLeft(ndlst *lst, int n)
{
    if (lst->len <= 1)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int tmp = lst->head->data;
        for (dlnode *cur_node = lst->head; cur_node->next; cur_node = cur_node->next)
        {
            cur_node->data = cur_node->next->data;
        }
        lst->tail->data = tmp;
    }
}

// rotate the list n times to the right, assume, lst not empty
void dlistRotateRight(ndlst *lst, int n)
{
    if (lst->len <= 1)
    {
        return;
    }

    for (int i = 0; i < n; i++)
    {
        int tmp = lst->tail->data;
        for (dlnode *cur_node = lst->tail; cur_node->prev; cur_node = cur_node->prev)
        {
            cur_node->data = cur_node->prev->data;
        }
        lst->head->data = tmp;
    }
}

int main(void)
{
    ndlst *lst1 = dlistCreate();
    assert(dlistLength(lst1) == lst1->len);
    assert(dlistLength(lst1) == 0);
    dlistAddToFront(lst1, -20);
    dlistAddToEnd(lst1, 10);
    dlistAddToFront(lst1, 0);
    dlistAddToEnd(lst1, 9);
    dlistAddToFront(lst1, -9);
    dlistAddToFront(lst1, 7);
    dlistAddToEnd(lst1, 40);
    assert(dlistLength(lst1) == lst1->len);
    assert(dlistLength(lst1) == 7);
    dlistPrint(lst1);
    dlistPrintReverse(lst1);
    dlistRemoveElem(lst1, 5);
    dlistRemoveElem(lst1, 1);
    dlistRemoveElem(lst1, 5);
    dlistAddToEnd(lst1, 100);
    assert(dlistLength(lst1) == lst1->len);
    assert(dlistLength(lst1) == 5);
    dlistPrint(lst1);
    dlistPrintReverse(lst1);
    dlistSort(lst1);
    dlistPrint(lst1);
    dlistRotateLeft(lst1, 2);
    dlistPrint(lst1);
    dlistRotateRight(lst1, 3);
    dlistPrint(lst1);
    dlistDestroy(lst1);

    printf("\n");
    ndlst *l0 = dlistCreate();
    ndlst *l1 = dlistCreate();
    ndlst *l2 = dlistCreate();
    ndlst *l3 = dlistCreate();
    ndlst *l4 = dlistCreate();

    printf("After init:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistAddToFront(l0, 0);

    dlistAddToFront(l1, 0);
    dlistAddToFront(l1, 1);

    dlistAddToFront(l2, 0);
    dlistAddToFront(l2, 1);
    dlistAddToFront(l2, 2);

    dlistAddToFront(l3, 0);
    dlistAddToFront(l3, 1);
    dlistAddToFront(l3, 2);
    dlistAddToFront(l3, 3);

    dlistAddToFront(l4, 0);
    dlistAddToFront(l4, 1);
    dlistAddToFront(l4, 2);
    dlistAddToFront(l4, 3);
    dlistAddToFront(l4, 4);

    printf("After add:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistRemoveElem(l0, 1);
    dlistRemoveElem(l1, 1);
    dlistRemoveElem(l2, 1);
    dlistRemoveElem(l3, 1);
    dlistRemoveElem(l4, 1);

    printf("After 1 round of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistRemoveElem(l1, 1);
    dlistRemoveElem(l2, 1);
    dlistRemoveElem(l3, 1);
    dlistRemoveElem(l4, 1);

    printf("After 2 rounds of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistRemoveElem(l2, 1);
    dlistRemoveElem(l3, 1);
    dlistRemoveElem(l4, 1);

    printf("After 3 rounds of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    printf("After 4 rounds of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistRemoveElem(l3, 1);
    dlistRemoveElem(l4, 1);

    printf("After 5 rounds of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistRemoveElem(l4, 1);

    printf("After 6 rounds of remove:\n");
    printf("%d\n", dlistLength(l0));
    printf("%d\n", dlistLength(l1));
    printf("%d\n", dlistLength(l2));
    printf("%d\n", dlistLength(l3));
    printf("%d\n", dlistLength(l4));
    dlistPrintReverse(l0);
    dlistPrintReverse(l1);
    dlistPrintReverse(l2);
    dlistPrintReverse(l3);
    dlistPrintReverse(l4);

    dlistDestroy(l0);
    dlistDestroy(l1);
    dlistDestroy(l2);
    dlistDestroy(l3);
    dlistDestroy(l4);
    printf("Complete\n");

    return 0;
}
