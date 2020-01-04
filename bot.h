#ifndef FIVE_BOT_H
#define FIVE_BOT_H

int think(int *x, int *y, int dep);
int think_test(int *x, int *y, int dep, int player);
void init_bot();
int judge_break_global(int x, int y, int player);
int evaluate();
void load_pattern_from_file(char *filename);
//void output_pattern(char *filename)

#endif //FIVE_BOT_H
