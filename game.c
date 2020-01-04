#include<stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "five.h"
#include "bot.h"

const char ICON[2][10] = {".xo", ".XO"};
const char WINDOWS_ICON[2][3][10] = {{"", "¡ñ", "¡ð"}, {"", "¡ø", "¡÷"}};
const char WINDOWS_BOARD[3][3][10] = {{"©°", "©Ð", "©´"}, {"©À", "©à", "©È"}, {"©¸", "©Ø", "©¼"}};

const int D[8][2] = {{1, 0}, {0, 1}, {1, 1}, {1, -1}, {-1, 0}, {0, -1}, {-1, -1}, {-1, 1}};
int board[SIZE][SIZE], step;
int record[SIZE*SIZE];
int scope[2][2];
int enable_break, safe_mode, mode, human;

void clear_screen()
{
#ifdef linux
    system("clear");
#elif __WINDOWS_
    system("cls");
#elif _WIN32
    system("cls");
#endif
}

void get_line(char *s)
{
    int len = 0;
    while ((s[len++] = getchar()) != '\n');
    s[--len] = 0;
}

int get_int(const char *hint, int begin, int end)
{
    while(1)
    {
        char s[MAX_LINE];
        printf("%s: ", hint);
        get_line(s);
        putchar('\n');
        for (int i = 0; s[i]; i++)
            if (isdigit(s[i]) && s[i] - '0' <= end && s[i] - '0' >= begin)
            {
                printf("your choice is %d\n", s[i] - '0');
                return s[i] - '0';
            }

    }
}

void print_chessboard_linux()
{
    
#ifdef DEBUG
    printf("  \t");
    for(int i = 0; i < N; i++) printf("%c ", i < 10 ? i + '0' : i - 10 + 'A');
    putchar('\n');
#endif

    for(int i = 0; i < N; i++)
    {

        printf("%2d\t", N-i);
        for(int j = 0; j < N; j++)
        {
            int p = (step && record[step-1] == i*N+j) || (step-1 && record[step-2] == i*N+j);
            int q = board[i][j];
            printf("%c ", ICON[p][q]);
        }
#ifdef DEBUG
        printf("%c\t", i < 10 ? i + '0' : i - 10 + 'A');
#endif
        putchar('\n');
    }
    printf("  \t");
    for(int i = 0; i < N; i++) printf("%c ", 'A'+i);
    putchar('\n');
}

void print_chessboard_windows()
{
    for(int i = 0; i < N; i++)
    {
        printf("%2d\t", N-i);
        for(int j = 0; j < N; j++)
        {
            if(board[i][j])
            {
                int p = (step && record[step-1] == i*N+j) || (step-1 && record[step-2] == i*N+j);
                int q = board[i][j];
                printf("%s", WINDOWS_ICON[p][q]);
            }
            else
            {
                int p = i == 0 ? 0 : (i < N-1 ? 1 : 2);
                int q = j == 0 ? 0 : (j < N-1 ? 1 : 2);
                printf("%s", WINDOWS_BOARD[p][q]);
            }
        }
        putchar('\n');
    }
    printf("  \t");
    for(int i = 0; i < N; i++) printf("%c ", 'A'+i);
    putchar('\n');
}

void print_chessboard(int last_time, int enable_clear)
{
#ifndef DEBUG
    if(enable_clear) clear_screen();
#endif
	
    if(last_time >= 0) printf("last time: %ds\n", last_time);
    else printf("last time: --\n");

    printf("step: %d\n", step);
#ifdef linux
    print_chessboard_linux();
#else
    if(safe_mode) print_chessboard_linux();
    else print_chessboard_windows();
#endif

	if(step)
	{
		int player = opp((step&1)+1),
			lastx = record[step-1]/N,
			lasty = record[step-1]%N;
		printf("last step (%s): %c%d\n", player == BLACK ? "black" : "white", 'A' + lasty, 15 - lastx);
		printf("rating: %d\n", evaluate());
	}
}

void read_chessboard()
{
    char s[MAX_LINE];
    int black = 0, white = 0;
    for(int i = 0; i < N; i++)
    {
        get_line(s);
        int j = 0;
        while(s[j] != '.' && s[j] != 'x' && s[j] != 'X' && s[j] != 'o' && s[j] != 'O') j++;

        for(int k = 0; k < N; k++)
        {
            switch(s[j])
            {
                case '.': board[i][k] = EMPTY; break;
                case 'x': board[i][k] = BLACK; black++; break;
                case 'X': board[i][k] = BLACK; black++; break;
                case 'o': board[i][k] = WHITE; white++; break;
                case 'O': board[i][k] = WHITE; white++; break;
            }
            j += 2;
        }
        if(black > white) step = 1;
        else step = 2;
    }
}

int get_input(int *x, int *y)
{
    char s[MAX_LINE];
    while(1)
    {
        char col = 0; int row = 0;
        printf("%s's turn (enter colomn+row. E.g. H8): ", step%2 ? "white" : "black");
        get_line(s);
        for(int i = 0; s[i]; i++)
        {
            if('a' <= s[i] && s[i] <= 'z') col = s[i] + 'A' -'a';
            else if('A' <= s[i] && s[i] <= 'Z') col = s[i];
            else if('0' <= s[i] && s[i] <= '9')
            {
                row = s[i] - '0';
                if('0' <= s[i+1] && s[i+1] <= '9') row = row * 10 + s[i+1] - '0';
                break;
            }
        }

        if('A' <= col && col <= 'O' && 1 <= row && row <= 15)
        {
            *x = N - row; *y = col - 'A';
            break;
        }
        if(mode == MODE_HC && col == 'R' && step >= 2)
        {
            board[record[step-1]/N][record[step-1]%N] = 0;
            board[record[step-2]/N][record[step-2]%N] = 0;
            step -= 2;
            print_chessboard(-1, 1);
            printf("traceback 1 step\n");
            continue;
        }
        printf("invalid input!\n");
    }
    return -1;
}

int judge()
{
    int empty = 0;
    for(int i = 0; i < 15; i++)
        for(int j = 0; j < 15; j++)
        {
            for(int k = 0; k < 4; k++)
            {
                if(!in(i+D[k][0]*4, j+D[k][1]*4)) continue;
                int cnt[3] = {0, 0, 0};
                for(int l = 0; l < 5; l++)
                    cnt[abs(board[i+D[k][0]*l][j+D[k][1]*l])]++;
                if(cnt[1] == 5) return BLACK_WIN;
                if(cnt[2] == 5) return WHITE_WIN;
            }
            empty |= board[i][j] == 0;
        }
    return empty ? VALID : TIE;
}

int interact(int x, int y)
{
    if(board[x][y]) return INVALID;
    int player = step%2 + 1;
    board[x][y] = player;
    record[step] = x*N+y;
    if(enable_break && player == BLACK && judge_break_global(x, y, player))
    {
        if(mode == MODE_HC)
        {
            if(human == BLACK)
            {
                int cont = get_int("black seems break the rule, continue playing? (0/1)", 0, 1);
                if(!cont) return BREAK_RULE;
            }
        }
        else return BREAK_RULE;
    }

    scope[0][0] = min(scope[0][0], x);
    scope[0][1] = max(scope[0][1], x);
    scope[1][0] = min(scope[0][0], y);
    scope[1][1] = max(scope[0][1], y);

    step++;
    return judge();
}

int play_hh()
{
    while(1)
    {
        int x, y, state = -1;
        do
        {
            if(state == INVALID) printf("invalid input!\n");
            get_input(&x, &y);
            state = interact(x, y);
        }
        while(state == INVALID);
        print_chessboard(-1, 1);

#ifdef DEBUG
        extern int evaluate();
        printf("rating: %d\n", evaluate());
#endif
		if(state != VALID)
		{
			if(state == BREAK_RULE)
			{
				printf("black breaks the rule!\n");
				return WHITE_WIN;
			}
			return state;
		}
    }
}

int play_hc()
{
    human = get_int("enter 1 to choose black, 2 choose white", BLACK, WHITE);
    int dep = get_int("choose ai level from 0 to 6", 0, 6);

    while(1)
    {
        int x, y, state = -1;
        int last_time = -1;
        do
        {
            if(state == INVALID) printf("invalid input!\n");
            int player = (step&1)+1;
            last_time = player == human ? get_input(&x, &y) : think(&x, &y, dep);
            state = interact(x, y);

        } while(state == INVALID);

        print_chessboard(last_time, 1);
        if(state != VALID)
        {
            if(state == BREAK_RULE)
            {
                printf("black breaks the rule!\n");
                return WHITE_WIN;
            }
            return state;
        }
    }
}

int play_cc()
{
    int dep1 = get_int("choose black's level from 0 to 6", 0, 6);
    int dep2 = get_int("choose white's level from 0 to 6", 0, 6);
    while(1)
    {
        int x, y, state = -1;
        int last_time = -1;
        do
        {
            if(state == INVALID) printf("invalid input!\n");
            int player = (step&1)+1;
            last_time = think(&x, &y, player == BLACK ? dep1 : dep2);


            state = interact(x, y);

        } while(state == INVALID);

        print_chessboard(last_time, 1);
        if(state != VALID)
        {
            if(state == BREAK_RULE)
            {
                printf("black breaks the rule!\n");
                return WHITE_WIN;
            }

            return state;
        }
    }
}

void play_debug()
{
    init_bot();
    printf("enter chessboard: \n");
    read_chessboard();
    int dep = get_int("depth", 0, 10);
    int x, y;
    int last_time = think(&x, &y, dep);
    printf("(%d, %d)\n", x, y);
    interact(x, y);
    print_chessboard(last_time, 0);
}


void init_game()
{
    memset(board, 0, sizeof(board));
    step = 0;
    memset(record, 0, sizeof(record));
    init_bot();
    scope[0][0] = scope[1][0] = N;
    scope[0][1] = scope[1][1] = 0;
	print_chessboard(-1, 1);
}
