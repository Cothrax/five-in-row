#ifndef FIVE_GAME_H
#define FIVE_GAME_H

void clear_screen();
int play_cc();
int play_hc();
int play_hh();
void play_debug();
void print_chessboard(int last_time, int enable_clear);
int interact(int x, int y);
void init_game();
void get_line(char *s);
int get_int(const char *hint, int begin, int end);

#endif //FIVE_GAME_H
