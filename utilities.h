#ifndef FIVE_UTILITIES_H
#define FIVE_UTILITIES_H
#include "five.h"

struct ListNode
{
    struct ListNode *l, *r;
    int x, y;
};

struct LinkedList
{
    int size;
    struct ListNode *head, *tail;
    struct ListNode *loc[N][N];
};

struct CacheList { int x[25], y[25], top; };

struct Queue
{
    int x[SIZE*SIZE], y[SIZE*SIZE], visited[SIZE][SIZE], top;
};

inline static int Queue_push_back(struct Queue *queue, int x, int y)
{
    if(!queue->visited[x][y])
    {
        queue->x[queue->top] = x;
        queue->y[queue->top] = y;
        queue->visited[x][y] = queue->top + 1;
        queue->top++;
        return queue->top;
    }
    return 0;
}

inline static void Queue_clear(struct Queue *queue)
{
    memset(queue->visited, 0, sizeof(queue->visited));
    queue->top = 0;
}

inline static struct ListNode *LinkedList_push_back(struct LinkedList *list, int x, int y)
{
//    printf("2 %d %d\n", x, y);
    if(!list->loc[x][y])
    {
        struct ListNode *node = malloc(sizeof(struct ListNode));
        node->l = list->tail;
        node->r = NULL;
        node->x = x;
        node->y = y;

        if(!list->size) list->head = node;
        else list->tail->r = node;
        list->tail = node;
        list->loc[x][y] = node;
        list->size++;
//        printf("malloc: %p\n", node);
        return node;
    }
    return NULL;
}

inline static void LinkedList_erase(struct LinkedList *list, struct ListNode *node)
{
//    printf("3 %d %d\n", node->x, node->y);
    if(node && list->loc[node->x][node->y] == node)
    {
        if(node->l) node->l->r = node->r;
        if(node->r) node->r->l = node->l;
        if(list->head == node) list->head = node->r;
        if(list->tail == node) list->tail = node->l;

        list->size--;
//        printf("(%d. %d)\n", node->x, node->y);
        list->loc[node->x][node->y] = NULL;
//        printf("%p (%d, %d) free %p\n", list, node->x, node->y, node);
        free(node);
    }
}

inline static void LinkedList_erase_by_loc(struct LinkedList *list, int x, int y)
{
    if(list->loc[x][y]) LinkedList_erase(list, list->loc[x][y]);
}


inline static void LinkedList_float_move(struct LinkedList *list, struct ListNode *node)
{
//    printf("4 %d %d\n", node->x, node->y);
    if(node == list->head) return;
    if(node->l) node->l->r = node->r;
    if(node->r) node->r->l = node->l;
    if(list->tail == node) list->tail = node->l;

    node->r = list->head;
    node->l = NULL;
    list->head->l = node;
    list->head = node;
}

inline static struct ListNode *LinkedList_swap_move(struct LinkedList *list, struct ListNode *node)
{
//    printf("5 %d %d\n", node->x, node->y);
    if(!node->l) return node;
    struct ListNode *other = node->l;
    if(other->l) other->l->r = node;
    if(node->r) node->r->l = other;

    node->l = other->l;
    other->r = node->r;
    node->r = other;
    other->l = node;

    if(list->head == other) list->head = node;
    if(list->tail == node) list->tail = other;
    return other;
}

inline static void LinkedList_init(struct LinkedList *list)
{
    list->size = 0;
    list->head = list->tail = NULL;
    memset(list->loc, 0, sizeof(list->loc));
}

inline static void LinkedList_clear(struct LinkedList *list)
{
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(list->loc[i][j] != NULL)
            {
//                printf("free %p\n", list->loc[i][j]);
                free(list->loc[i][j]);
                list->loc[i][j] = NULL;
            }
    list->size = 0;
    list->head = list->tail = NULL;
}

inline static void CacheList_push_back(struct CacheList *list, int x, int y)
{
    list->x[list->top] = x;
    list->y[list->top] = y;
    list->top++;
}


#endif //FIVE_UTILITIES_H
