#ifndef FIVE_FIVE_H
#define FIVE_FIVE_H

#define SIZE 20					// default array size
#define MAX_LINE 1000			// char array size
#define N 15					// chessboard size
#define INF 0x3f3f3f3f

// 模式常量
#define MODE_NUM 6
#define MODE_HH 0
#define MODE_HC 1
#define MODE_CC 2
#define MODE_DEBUG 3
#define MODE_SAFE 4
#define MODE_QUIT 5

#define BLACK 1
#define WHITE 2

// 结果常量
#define INVALID 0
#define VALID 3
#define BLACK_WIN 1
#define WHITE_WIN 2
#define BREAK_RULE 4
#define TIE 5

// 匹配串的字符常量
#define CHARSET_SIZE 4
#define EMPTY 0
#define PLAYER 1
#define OPPONENT 2
#define BORDER 3				/* 边界 */

//匹配串的通配符常量
#define NO_BLACK 'B'			/* 不能是黑子 */
#define NO_WHITE 'W'			/* 不能是白子 */
#define NO_EMPTY_BLACK 'L'		/* 不能是黑子或空子 */
#define NO_EMPTY_WHITE 'H'		/* 不能是白子或空子 */
#define ANYTHING 'A'			/* 任意 */


// 特征常量
#define TAGS_SIZE 4
#define LIVE3 1					/* 活三 */
#define LIVE4 2					/* 活四 */
#define LONG 3					/* 长连 */

#define ll long long
#define ull unsigned long long
#define in(x, y) ((x)>=0&&(x)<N&&(y)>=0&&(y)<N)
//#define abs(x) ((x)>0?(x):-(x))
#define sgn(x) ((x<0)?-1:(x>0))
#define swap(x, y) {if(x!=y)x=y-x,y=y-x,x=x+y;}
#define max(x, y) ((x)>=(y)?(x):(y))
#define min(x, y) ((x)<=(y)?(x):(y))
#define opp(player) (3^(player))

#endif //FIVE_FIVE_H
