#ifndef FIVE_BOT_H
#define FIVE_BOT_H

// AI接口
int think(int *x, int *y, int dep); /* AI入口 */
void init_bot();					/* AI初始化 */
int judge_break_global(int x, int y, int player); /* player下在(x, y)处的禁手判断 */
int evaluate();									  /* 评估函数 */

#endif //FIVE_BOT_H
