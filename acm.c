#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include <string.h>
#include "five.h"
#include "acm.h"

extern int D[8][2];
extern int board[SIZE][SIZE];

static struct TrieNode *new_node()
{
    struct TrieNode *ret = malloc(sizeof(struct TrieNode));
    ret->val = 0;
    ret->tag = 0;
    ret->fail = NULL;
    for(int i = 0; i < CHARSET_SIZE; i++) ret->ch[i] = NULL;
    return ret;
}

void ACM_init(struct ACM *acm)
{
    acm->size = 1;
    acm->root = new_node();
}

static void insert(struct ACM *acm, char *s, int val, int tag, int is_rev)
{
#ifdef DEBUG
    printf("insert: val=%d, tag=%d: ", val, tag);
#endif
    struct TrieNode *u = acm->root;
    for(int i = 0; i < s[i]; i++)
    {
        int c = s[i] - '0';
        if((c == BLACK || c == WHITE) && is_rev) c = BLACK + WHITE - c;
#ifdef DEBUG
        printf("%c", c+'0');
#endif
        if (u->ch[c] == NULL) u->ch[c] = new_node(), acm->size++;
        u = u->ch[c];
    }
#ifdef DEBUG
    putchar('\n');
#endif
    u->val = val;
    u->tag = tag;
}

static void dfs_pattern(struct ACM *acm, char *s, char *cur, int val, int tag, int is_rev)
{
    if(*cur == '\0')
    {
//        printf("insert %s, val=%d, tag=%d, is_rev=%d\n", s, val, tag, is_rev);
        insert(acm, s, val, tag, is_rev);
        return;
    }
    if(isdigit(*cur)) dfs_pattern(acm, s, cur+1, val, tag, is_rev);
    else
    {
        int flg[CHARSET_SIZE];
        for(int i = 0; i < CHARSET_SIZE; i++) flg[i] = 1;
        switch(*cur)
        {
            case NO_BLACK: flg[BLACK] = 0; break;
            case NO_WHITE: flg[WHITE] = 0; break;
            case NO_EMPTY_BLACK: flg[BLACK] = flg[EMPTY] = 0; break;
            case NO_EMPTY_WHITE: flg[WHITE] = flg[EMPTY] = 0; break;
        }
        for(int i = 0; i < CHARSET_SIZE; i++)
            if(flg[i])
            {
                char tmp = *cur;
                *cur = i + '0';
                dfs_pattern(acm, s, cur+1, val, tag, is_rev);
                *cur = tmp;
            }
    }
}

void ACM_insert(struct ACM *acm, char *s, int val, int tag, int is_rev)
{
    dfs_pattern(acm, s, s, val, tag, is_rev);
}

void ACM_build_fail(struct ACM *acm)
{
    struct TrieNode **q = malloc(sizeof(struct TrieNode*) * acm->size), *u = NULL;
    q[0] = acm->root;
    for(int h = 0, t = 1; h != t; h++)
        for(int c = 0; c < CHARSET_SIZE; c++)
        {
            if((u = q[h])->ch[c] == NULL) continue;
            struct TrieNode *v = u->ch[c];
            if(u == acm->root) v->fail = acm->root;
            else
            {
                u = u->fail;
                while(u != acm->root && u->ch[c] == NULL) u = u->fail;
                v->fail = u->ch[c] == NULL ? 0 : u->ch[c];
            }
            q[t++] = v;
        }
    free(q);
}

inline static struct TrieNode *parse_node(struct ACM *acm, struct TrieNode *u, int c, int *rating)
{
//    printf("%c (%p) (%p) ", c+'0', u, u->ch[c]);
    if(u->ch[c] != NULL) u = u->ch[c];
    else
    {
        while(u != acm->root && u->ch[c] == NULL) u = u->fail;
        u = u->ch[c] == NULL ? acm->root : u->ch[c];
    }

    *rating += u->val;
    return u;
}


inline static struct TrieNode *parse_node_with_tags(struct ACM *acm, struct TrieNode *u, int c, int *rating, int *tags)
{
    if(u->ch[c] != NULL) u = u->ch[c];
    else
    {
        while(u != acm->root && u->ch[c] == NULL) u = u->fail;
        u = u->ch[c] == NULL ? 0 : u->ch[c];
    }
    *rating += u->val;
    tags[u->tag]++;
    return u;
}

int ACM_query_rating(struct ACM *acm, int player, int x, int y, int x1, int y1, int dx, int dy)
{
//    printf("(%d, %d) - (%d, %d), d = (%d, %d)\n", x, y, x1, y1, dx, dy);
//    printf("(%d, %d) -> (%d, %d): ", x, y, x1, y1);
    struct TrieNode *u = acm->root;
    int rating = 0;
    u = parse_node(acm, u, BORDER, &rating);
    for(; x != x1 || y != y1; x += dx, y += dy)
        u = parse_node(acm, u, board[x][y], &rating);
    u = parse_node(acm, u, BORDER, &rating);

//    printf("\nrating=%d\n", player == BLACK ? rating : -rating);
    return player == BLACK ? rating : -rating;
}

int ACM_query_rating_with_tags(struct ACM *acm, int player, int x, int y, int x1, int y1, int dx, int dy, int *tags)
{
    struct TrieNode *u = acm->root;
    int rating = 0;
    u = parse_node(acm, u, BORDER, &rating);
    for(; x != x1 || y != y1; x += dx, y += dy)
        u = parse_node_with_tags(acm, u, board[x][y], &rating, tags);
    u = parse_node(acm, u, BORDER, &rating);
    return player == BLACK ? rating : -rating;
}

void ACM_walk(struct TrieNode *u, int dep)
{
    printf("%p(%d) fail=%p\n", u, u->val, u->fail);
    for(int i = 0; i < CHARSET_SIZE; i++)
        if(u->ch[i] != NULL)
        {
            for(int _ = 0; _ < dep; _++) printf("  ");
            printf("-%d-> ", i);
            ACM_walk(u->ch[i], dep + 1);
        }
}
