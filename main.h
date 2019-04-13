#pragma once

#define MAXSIZE 10

//一些图案
#define PAT_BALL "●"
#define PAT_BOX  "□"
#define PAT_BLANK "　"
#define PAT_SELECTED "★"
#define PAT_DELETED "○"
#define PAT_BALL_IN_BOX "○"
#define PAT_SEL_BALL_IN_BOX "☆"

//坐标结构
struct coord {
    union {
        struct {
            int r;
            int c;
        };
        struct {
            int y;
            int x;
        };
    };
};
//bfs节点
struct node
{
    union {
        struct {
            int r;
            int c;
        };
        struct {
            int y;
            int x;
        };
    };
    int parent;
    int step;
};

enum ball_type {
    normal,
    selected,
    box,
    normal_with_box,
    selected_with_box,
    deleted,
    none
};
//打印一个球
void printElem(int board[][MAXSIZE], coord size, coord pos, coord board_offset, ball_type type);
//寻路,返回路径数组
bool bfs(int (*board)[MAXSIZE], coord size, coord start, coord end, coord*path);
//判断能否清除
int canclear(int (*board)[MAXSIZE], coord size, coord pos, coord*clear_set);

//移动动画
void dmove(int (*board)[MAXSIZE], coord size, coord offset, coord *path);
//清除动画
void dclear(int (*board)[MAXSIZE], coord size, coord offset, coord*clear_set);
//清除
void clear(int(*board)[MAXSIZE], coord*clear_set, int clear_count[8]);
//清除输入中的一行
void clearstdin();

//读取数字
int getnum(int min, int max);

//判断游戏是否结束
bool game_over(int (*board)[MAXSIZE], coord size);
//初始化棋盘,生成初始球
int generate(int (*board)[MAXSIZE], coord size, int count);
//输入行列
void getRandC(coord &size);
//插入新球
int insert(int (*board)[MAXSIZE], coord size, int ball);
//画表格有分割线版本
void paint_board_with_line(int (*board)[MAXSIZE], coord size, coord offset,bool update);
//画表格没分割线版本
void paint_board(int (*board)[MAXSIZE], coord size);
//画接下来的3个球
void paint_next(int *next, coord offset, bool update);
//画分数
void paint_score(int score, coord offset,bool update);
//画统计信息
void paint_stat(int (*board)[MAXSIZE], coord size, coord offset, int clear_set[8],bool update);
//打印数组
void print_board(int (*board)[MAXSIZE], coord size);
//计分
int get_score(int clear_count[8]);

void func1();
void func2();
void func3();
void func4();
void func5();
void func6();
void func7();
void func8();