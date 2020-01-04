#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <time.h>

#include "utilities.h"
#include "five.h"
#include "acm.h"
#include "scores.h"

#define THRESHOLD 90000
#define THINK_TIMEOUT 15
#define OPTIMISTIC_DEPTH 4
extern int D[8][2];
extern int step;
extern int board[SIZE][SIZE];
extern int scope[2][2];
extern int enable_break;
extern int judge();

struct ACM evaluator;			/* 用于评估函数计算的AC自动机 */
struct Queue available;			/* 按经验排序的初始空子序列 */
struct LinkedList history[8];	/* 每一层启发式优化的空子序列 */
int sign[3];

void init_bot()
{
    if(evaluator.size) return;
    char *pattern;
    int value, tag, can_flip, can_rev;

    ACM_init(&evaluator);
    for(int i = 0; i < pattern_num; i++)
    {
        pattern = score_patterns[i];
        value = score_ratings[i];
        tag = score_tags[i];
        can_flip = score_can_flips[i];
        can_rev = score_can_revs[i];

        ACM_insert(&evaluator, pattern, value, tag, 0);
        if(can_flip) ACM_insert(&evaluator, pattern, -value, 0, 1);
        if(can_rev)
        {
            int n = strlen(pattern);
            for(int k = 0; k < n-1-k; k++)
            {
                char tmp = pattern[k];
                pattern[k] = pattern[n-1-k];
                pattern[n-1-k] = tmp;
            }
            ACM_insert(&evaluator, pattern, value, tag, 0);
        }
    }
    ACM_build_fail(&evaluator);

#ifdef DEBUG
    printf("\n after: \n");
    ACM_walk(evaluator.root, 0);
#endif
}

int evaluate()
{
    int player = (step&1)+1, rating = 0;
    for(int i = 0; i < N; i++) rating += ACM_query_rating(&evaluator, player, 0, i, N, i, 1, 0);
    for(int i = 0; i < N; i++) rating += ACM_query_rating(&evaluator, player, i, 0, i, N, 0, 1);
    // (i, 0) -> (N-1, N-1-i)
    // (0, i) -> (N-1-I, N-1)
    for(int i = 0; i < N-4; i++)
    {
        rating += ACM_query_rating(&evaluator, player, i, 0, N, N - i, 1, 1);
        if(i) rating += ACM_query_rating(&evaluator, player, 0, i, N - i, N, 1, 1);
    }
    for(int i = N-1; i >= 4; i--)
    {
        rating += ACM_query_rating(&evaluator, player, 0, i, i + 1, -1, 1, -1);
        if(i != N-1) rating += ACM_query_rating(&evaluator, player, N - 1 - i, N - 1, N, N - 2 - i, 1, -1);
    }
    return rating;
}

inline static int evaluate_partial(int x, int y)
{
    int player = (step&1)+1;
    int rating = 0;
    rating += ACM_query_rating(&evaluator, player, x, 0, x, N, 0, 1);
    rating += ACM_query_rating(&evaluator, player, 0, y, N, y, 1, 0);
    int k = y - x;
    rating += ACM_query_rating(&evaluator, player, max(0, -k), max(0, k), min(N - k, N), min(N + k, N), 1, 1);
    k = y + x;
    rating += ACM_query_rating(&evaluator, player, max(-N+k+1, 0), min(k, N-1), min(k+1, N), max(-N+k, -1), 1, -1);
    return rating;
}

inline static int evaluate_partial_with_break(int x, int y, int tags[])
{
    int player = (step&1)+1;
    int rating = 0;
    for(int i = 0; i < TAGS_SIZE; i++) tags[i] = 0;

    rating += ACM_query_rating_with_tags(&evaluator, player, x, 0, x, N, 0, 1, tags);
    rating += ACM_query_rating_with_tags(&evaluator, player, 0, y, N, y, 1, 0, tags);
    int k = y - x;
    rating += ACM_query_rating_with_tags(&evaluator, player, max(0, -k), max(0, k), min(N - k, N), min(N + k, N), 1, 1, tags);
    k = y + x;
    rating += ACM_query_rating_with_tags(&evaluator, player, max(-N+k+1, 0), min(k, N-1), min(k+1, N), max(-N+k, -1), 1, -1, tags);
    return rating;
}

static inline void bfs_partial(struct Queue *queue, int x, int y)
{
    for(int i = x-2; i < x+3; i++)
        for(int j = y-2; j < y+3; j++)
            if(in(i, j) && !board[i][j]) Queue_push_back(queue, i, j);
}

static inline void bfs_partial_into_history(int dep, int x, int y, struct CacheList *used)
{
    used->top = 0;
    for(int i = x-2; i < x+3; i++)
        for(int j = y-2; j < y+3; j++)
            if(in(i, j) && !board[i][j])
                if(!history[dep - 1].loc[i][j])
                {
                    for(int k = dep-1; k > 0; k--)
                    {
                        assert(!history[k].loc[i][j]);
                        LinkedList_push_back(&history[k], i, j);
                    }
                    CacheList_push_back(used, i, j);
                }
}

static inline void traceback_history(int dep, struct CacheList *used)
{
    for(int i = 0; i < used->top; i++)
        for(int k = dep-1; k >= 0; k--)
            LinkedList_erase_by_loc(&history[k], used->x[i], used->y[i]);
}

inline static int judge_break(int *prev_tags, int *succ_tags)
{
//    for(int i = 0; i < TAGS_SIZE; i++) printf("%d %d\n", prev_tags[i], succ_tags[i]);
//    printf("%d %d %d\n", succ_tags[LONG], succ_tags[LIVE3] - prev_tags[LIVE3], succ_tags[LIVE4] - prev_tags[LIVE4]);
	if(succ_tags[LONG] - prev_tags[LONG] > 0) return 0;
	if(succ_tags[LIVE3] - prev_tags[LIVE3] >= 2) return 0;
    if(succ_tags[LIVE4] - prev_tags[LIVE4] >= 2) return 0;
	return 1;
}

int judge_break_global(int i, int j, int player)
{
//    printf("(%d, %d) %d\n", i, j, player);
    board[i][j] = 0;
    int prev_tags[TAGS_SIZE], succ_tags[TAGS_SIZE];
    evaluate_partial_with_break(i, j, prev_tags);

    board[i][j] = player;
    evaluate_partial_with_break(i, j, succ_tags);

#ifdef DEBUG
	for(int k = 0; k< TAGS_SIZE; k++)
		printf("%d %d\n", prev_tags[k], succ_tags[k]);
	printf("judge_break = %d\n", judge_break(prev_tags, succ_tags));
#endif
	
    return !judge_break(prev_tags, succ_tags);
}

inline static int potential(struct Queue *queue, int k)
{
    int i = queue->x[k], j = queue->y[k];
    int prev_value = evaluate_partial(i, j);
    board[i][j] = PLAYER;
    int succ_value1 = evaluate_partial(i, j);
    board[i][j] = OPPONENT;
    int succ_value2 = evaluate_partial(i, j);
    board[i][j] = 0;
    return abs(succ_value1-prev_value) + abs(succ_value2-prev_value);
}

void qsort_queue(struct Queue *queue, int l, int r, int cx, int cy)
{
#define distance(i) (abs(queue->x[i] - cx) + abs(queue->y[i] - cy))
#define value(i) 2*N*potential(queue, i) + 2*N - distance(i)
    int k = rand()%(r-l+1) + l;
    int i = l, j = r, x = value(k);
    do
    {
        while(value(i) > x) i++;
        while(value(j) < x) j--;
        if(i <= j)
        {
            swap(queue->x[i], queue->x[j]);
            swap(queue->y[i], queue->y[j]);
            i++; j--;
        }
    }
    while(i <= j);
    if(i < r) qsort_queue(queue, i, r, cx, cy);
    if(j > l) qsort_queue(queue, l, j, cx, cy);
}

void bfs(struct Queue *queue)
{
    Queue_clear(queue);
    int cx = (scope[0][0] + scope[1][0])/2;
    int cy = (scope[0][1] + scope[1][1])/2;
    for(int i = 0; i < N; i++)
        for(int j = 0; j < N; j++)
            if(board[i][j]) bfs_partial(queue, i, j);
    srand(time(NULL));
    qsort_queue(queue, 0, queue->top-1, cx, cy);
}

void init_history(int dep)
{
    for(int j = 0; j <= dep; j++)
    {
        LinkedList_init(&history[j]);
        for(int i = 0; i < available.top; i++)
            LinkedList_push_back(&history[j], available.x[i], available.y[i]);
    }
}

void clear_history(int dep)
{
    for(int i = 0; i <= dep; i++) LinkedList_clear(&history[i]);
}

int alpha_beta_search_with_break(int alpha, int beta, int dep, int player, int rating)
{
    if(dep <= 0 || judge() != VALID) return sign[player] * rating;
    int best_rating = -INF;

    struct CacheList used;
    for(struct ListNode *u = history[dep].head; u; u = u->r)
    {
        int i = u->x, j = u->y;
        if(board[i][j]) continue;

        int prev_rating, succ_rating, valid = 1;
        if(enable_break && player == BLACK)
        {
            int prev_tags[TAGS_SIZE], succ_tags[TAGS_SIZE];
            prev_rating = evaluate_partial_with_break(i, j, prev_tags);
            board[i][j] = player;
            succ_rating = evaluate_partial_with_break(i, j, succ_tags);
            valid = judge_break(prev_tags, succ_tags);
        }
        else
        {
            prev_rating = evaluate_partial(i, j);
            board[i][j] = player;
            succ_rating = evaluate_partial(i, j);
        }

        if(valid)
        {
            bfs_partial_into_history(dep, i, j, &used);

//        assert_list(&history[dep-1]);
//        assert_list(&history[dep]);
            int cur = -alpha_beta_search_with_break(-beta, -alpha, dep-1, opp(player), rating - prev_rating + succ_rating);

            board[i][j] = 0;
            traceback_history(dep, &used);

//        assert_list(&history[dep-1]);
//        assert_list(&history[dep]);

            if(cur > alpha)
            {
                if(cur >= beta)
                {
                    LinkedList_float_move(&history[dep], u);
                    return cur;
                }
                u = LinkedList_swap_move(&history[dep], u);
                alpha = cur;
            }
            best_rating = max(best_rating, cur);
        }
        board[i][j] = 0;
    }
    return best_rating;
}

int think_with_timeout(int *x, int *y, int max_dep, int timeout)
{
    ll start_time = time(NULL);

    if(step == 0) {*x = *y = 7; return time(NULL) - start_time;; }
    int player = (step&1)+1;

    bfs(&available);
    for(int k = 0; k < available.top; k++)
    {
        int i = available.x[k], j = available.y[k];
        board[i][j] = player;
        int res = judge();
        board[i][j] = 0;
        if(res == player || res == TIE)
        {
            *x = i; *y = j;
            return time(NULL) - start_time;
        }
    }
    init_history(max_dep);

    sign[player] = 1;
    sign[opp(player)] = -1;
    int best_rating = -INF;
    int cur_rating = evaluate();

    for(int dep = max_dep; dep >= 0 && best_rating < -THRESHOLD; dep--)
    {
#ifndef DEBUG
		printf("thinking at depth %d: %0.3f", dep, 0.);
#endif
        struct CacheList used;
        for(int k = 0; k < available.top; k++)
        {
            if(time(NULL) - start_time >= timeout - 2) dep = OPTIMISTIC_DEPTH;

            int i = available.x[k], j = available.y[k];
            if (board[i][j]) continue;
            int prev_rating, succ_rating, valid = 1;
            if(enable_break && player == BLACK)
            {
                int prev_tags[TAGS_SIZE], succ_tags[TAGS_SIZE];
                prev_rating = evaluate_partial_with_break(i, j, prev_tags);
                board[i][j] = player;
                succ_rating = evaluate_partial_with_break(i, j, succ_tags);
                valid = judge_break(prev_tags, succ_tags);
            }
            else
            {
                prev_rating = evaluate_partial(i, j);
                board[i][j] = player;
                succ_rating = evaluate_partial(i, j);
            }

//        assert(cur_rating - prev_rating + succ_rating == evaluate());

            if(valid)
            {
                bfs_partial_into_history(dep, i, j, &used);
                int cur = -alpha_beta_search_with_break(-INF, -best_rating, dep, opp(player),
                                                        cur_rating - prev_rating + succ_rating);
                if (cur > best_rating) *x = i, *y = j, best_rating = cur;
                traceback_history(dep, &used);
#ifdef DEBUG
                printf("dep=%d, %d(%d, %d) %d\n", dep, player, i, j, cur);
#else
				fflush(stdout);
				printf("\b\b\b\b\b%0.3f", 1.0*(k+1)/available.top);
#endif
            }
            board[i][j] = 0;
        }
		putchar('\n');
        if(time(NULL) - start_time >= timeout - 2) break;
    }
    clear_history(max_dep);
    return time(NULL) - start_time;
}

int think(int *x, int *y, int dep)
{
    return think_with_timeout(x, y, dep, THINK_TIMEOUT);
}
