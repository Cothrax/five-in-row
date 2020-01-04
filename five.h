#ifndef FIVE_FIVE_H
#define FIVE_FIVE_H

#define SIZE 20					// default array size
#define MAX_LINE 1000			// char array size
#define N 15					// chessboard size
#define INF 0x3f3f3f3f

#define MODE_NUM 6
#define MODE_HH 0
#define MODE_HC 1
#define MODE_CC 2
#define MODE_DEBUG 3
#define MODE_SAFE 4
#define MODE_QUIT 5

#define BLACK 1
#define WHITE 2

#define INVALID 0
#define VALID 3
#define BLACK_WIN 1
#define WHITE_WIN 2
#define BREAK_RULE 4
#define TIE 5

#define CHARSET_SIZE 4
#define EMPTY 0
#define PLAYER 1
#define OPPONENT 2
#define BORDER 3

#define TAGS_SIZE 4
#define LIVE3 1
#define LIVE4 2
#define LONG 3

#define NO_BLACK 'B'
#define NO_WHITE 'W'
#define NO_EMPTY_BLACK 'L'
#define NO_EMPTY_WHITE 'H'
#define ANYTHING 'A'

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
