#include <stdio.h>
#include <stdlib.h>
#include "five.h"
#include "game.h"

int main()
{
//    extern void output_pattern(char *filename);
//    output_pattern("score_new.txt");
    clear_screen();
    printf("Welcome to FiveInRow!\n\n\n");
    while(1)
    {
        extern int enable_break, mode, safe_mode;
        if(mode != MODE_SAFE)
            enable_break = get_int("enter\n"
                                   "\t1 to enable rule of forbidden move\n"
                                   "\t0 to disable it",
                                   0, 1);
        mode = get_int("enter\n"
                "\t0 for human-human mode,\n"
                "\t1 for human-computer mode,\n"
                "\t2 for computer-computer mode,\n"
                "\t3 for debug,\n"
                "\t4 to trigger safe mode,\n"
				"\t5 to quit", 0, MODE_NUM - 1);

        if(mode == MODE_QUIT) exit(0);
        if(mode == MODE_SAFE) safe_mode ^= 1;
        else if(mode == MODE_DEBUG) play_debug();
        else
        {
            int res = 0;
            init_game();
            switch(mode)
            {
                case MODE_HH: res = play_hh(); break;
                case MODE_HC: res = play_hc(); break;
                case MODE_CC: res = play_cc();
            }
#ifdef DEBUG
            printf("res=%d\n", res);
#endif
            switch(res)
            {
                case WHITE_WIN: printf("white win!\n"); break;
                case BLACK_WIN: printf("black win!\n"); break;
                case TIE: printf("tie!\n"); break;
                default: printf("I don't know what happened.\n");
            }
        }
    }
    return 0;
}
