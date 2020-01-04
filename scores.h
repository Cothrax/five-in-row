//
// Created by cothrax on 12/24/19.
//

#ifndef FIVE_SCORES_H
#define FIVE_SCORES_H

#define MAX_PATTERN_NUM 100
#define MAX_PATTERN_SIZE 10
/*
20
111111		-100000		3		0		0
B11111B		100000		0		0		0
A22222A		-100000		0		0		0
B011110B	9050		2		0		0
022220		-9050		0		0		0
01111L		7000		2		1		1
B10111B		7000		2		1		1
B11011B		7000		2		1		0
B01110B		5000		1		0		0
02220		-5000		0		0		0
B011010B	4900		1		0		1
A022020A	-4900		0		0		1
B0101010B	1000		0		0		0
A0202020A	-1000		0		0		0
L11100B		1000		0		1		1
L01011B		1000		0		1		1
001100		90			0		1		0
B01100		90			0		1		1
00100		20			0		1		0
B01000		20			0		1		1
 */
int pattern_num = 20;
char score_patterns[MAX_PATTERN_NUM][MAX_PATTERN_SIZE] = {
        "111111",
        "B11111B",
        "A22222A",
        "B011110B",
        "022220",
        "01111L",
        "B10111B",
        "B11011B",
        "B01110B",
        "02220",
        "B011010B",
        "A022020A",
        "B0101010B",
        "A0202020A",
        "L11100B",
        "L01011B",
        "001100",
        "B01100",
        "00100",
        "B01000"
};
int score_ratings[MAX_PATTERN_NUM] = {-100000, 100000, -100000, 9050, -9050, 7000, 7000, 7000, 5000, -5000, 4900, -4900, 1000, -1000, 1000, 1000, 90, 90, 20, 20  };
int score_tags[MAX_PATTERN_NUM] = {3, 0, 0, 2, 0, 2, 2, 2, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0  };
int score_can_flips[MAX_PATTERN_NUM] = {0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1  };
int score_can_revs[MAX_PATTERN_NUM] = {0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 0, 1  };

#endif //FIVE_SCORES_H
