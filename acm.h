#ifndef FIVE_ACM_H
#define FIVE_ACM_H
#include "acm.h"

struct TrieNode
{
    struct TrieNode *ch[CHARSET_SIZE], *fail;
    int val, tag;
};
struct ACM
{
    int size;
    struct TrieNode *root;
};

// AC自动机接口
void ACM_init(struct ACM *acm);	
void ACM_insert(struct ACM *acm, char *s, int val, int tag, int is_rev);
void ACM_build_fail(struct ACM *acm);
int ACM_query_rating(struct ACM *acm, int player, int x, int y, int x1, int y1, int dx, int dy);
int ACM_query_rating_with_tags(struct ACM *acm, int player, int x, int y, int x1, int y1, int dx, int dy, int *tags);

#ifdef DEBUG
void ACM_walk(struct TrieNode *u, int dep);
#endif

#endif //FIVE_ACM_H
