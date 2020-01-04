## 支持禁手的五子棋
> C语言大作业, 修复了Hash表的bug的版本（直接去掉了Hash表）

## Compile
### Visual Studio 2015
请使用release编译，并确认开启了（默认的）`/O2`优化

### CMake
推荐使用`CMake`编译，编译生成可执行文件`five`(Linux)/`five.exe`(Windows)
```bash
cmake .
make
```

### gcc
```bash
gcc --std=c99 -O3 *.c -o five
```

### 可能的编译错误和解决方案
1. game.c包含了绘制棋盘的字符，那些字符是GB2132编码，如果出现了编译错误，就把那个文件的编码改成GB2132。(仅Windows)
2. 请使用c99或以上的标准

## Notes
- AI的level对应搜索层数+1（这个版本可以搜6层），level 6速度太慢，效果不好
- 无法判断复杂禁手


## Algorithms
1. `acm.c`: AC自动机（用于模式匹配），用于评分函数和禁手判断
2. `bot.c`: AI实现（博弈搜索+AlphaBeta剪枝）
3. `five.c`: 程序入口
4. `game.c`: 游戏逻辑（模式逻辑，交互，输赢判断）
5. `scores.h`: 评分/禁手判断表
6. `utilities.h`: 包含队列和双向链表的实现，用于启发式优化
