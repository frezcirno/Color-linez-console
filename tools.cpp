#define _CRT_SECURE_NO_WARNINGS
#include "cmd_console_tools.h"
#include <iostream>
#include "main.h"
using namespace std;

int getnum(int min, int max)
{
    int x, y, ret;
    while (1)
    {
        getxy(x, y);
        scanf("%d", &ret);
        clearstdin();
        if (ret >= min && ret <= max)
            break;
        else
        {
            cout << "输入不合法，请重新输入";
            showstr(x, y, "          ");
            gotoxy(x, y);
        }
    }
    return ret;
}

void getRandC(coord &size)
{
    cls();
    setcolor();
    cout << "请输入行数(7-9)：";
    size.r = getnum(7, 9);
    cout << "请输入列数(7-9)：";
    size.c = getnum(7, 9);
}

bool bfs(int (*board)[MAXSIZE], coord size, coord start, coord end, coord *path)
{
    node queue[100] = {0};
    int tail, head;

    int visited[10][10] = {0};

    coord now, cat;
    coord dir[4] = {-1, 0, 0, 1, 1, 0, 0, -1};

    bool reached = false;

    tail = head = 0;

    queue[tail].r = start.r;
    queue[tail].c = start.c;
    queue[tail].parent = -1;
    queue[tail].step = 0;
    tail++;
    visited[start.r][start.c] = 1;

    while (tail != head && !reached)
    {
        now = {queue[head].r, queue[head].c};
        for (int i = 0; i < 4; i++)
        {
            cat = {now.r + dir[i].r, now.c + dir[i].c};
            if (cat.r < 0 || cat.r >= size.r || cat.c < 0 || cat.c >= size.c || board[cat.r][cat.c] != 0 || visited[cat.r][cat.c])
                continue;

            queue[tail].r = cat.r;
            queue[tail].c = cat.c;
            queue[tail].parent = head;
            queue[tail].step = queue[head].step + 1;
            visited[cat.r][cat.c] = 1;

            if (cat.r == end.r && cat.c == end.c)
            {
                reached = 1;
                break;
            }

            tail++;

        } //for dirs
        head++;
    }

    if (reached && path != NULL)
    {
        path[queue[tail].step + 1] = {-1, -1};
        while (tail != -1)
        {
            path[queue[tail].step] = {queue[tail].r, queue[tail].c};
            tail = queue[tail].parent;
        }
    }
    return reached;
}

void dclear(int (*board)[MAXSIZE], coord size, coord offset, coord *clear_set)
{
    coord now;
    coord *p = clear_set;
    while (p->r != -1)
    {
        now = *p;
        printElem(board, size, now, offset, deleted);
        p++;
    }
    Sleep(200);
    p = clear_set;
    while (p->r != -1)
    {
        now = *p;
        printElem(board, size, now, offset, none);
        p++;
    }
    return;
}
int get_score(int clear_count[8]) {
    int sum = 0;
    for (int i = 1; i < 8; i++) {
        sum += clear_count[i];
    }
    return (sum + 1)*(sum + 2);
}
void clear(int (*board)[MAXSIZE], coord *clear_set, int clear_count[8])
{
    int tmp;
    memset(clear_count, 0, 8 * sizeof(int));
    while (clear_set->r != -1)
    {
        tmp = board[clear_set->r][clear_set->c];
        clear_count[tmp]++;
        board[clear_set->r][clear_set->c] = 0;
        clear_set++;
    }
    return;
}

void dmove(int (*board)[MAXSIZE], coord size, coord offset, coord *path)
{
    coord now = {path[0].r, path[0].c};
    coord next;
    coord d;
    int fg_color = board[now.r][now.c] + 7;

    for (int i = 1; path[i].r != -1; i++)
    {
        next = { path[i].r, path[i].c };
        d.r = next.r - now.r;
        d.c = next.c - now.c;
        //清除
        showstr(offset.x + now.x * 4 + 2, offset.y + now.y * 2 + 1, PAT_BLANK, COLOR_WHITE, fg_color);
        //中间
        showstr(offset.x + now.x * 4 + d.x * 2 + 2, offset.y + now.y * 2 + d.y + 1, PAT_SELECTED, COLOR_WHITE, fg_color);
        Sleep(150);
        //复原
        showstr(offset.x + now.x * 4 + d.x * 2 + 2, offset.y + now.y * 2 + d.y + 1, (d.y == 0 ? "║" : "═"), COLOR_WHITE, COLOR_BLACK);
        //下一格
        showstr(offset.x + now.x * 4 + d.x * 4 + 2, offset.y + now.y * 2 + d.y * 2 + 1, PAT_SELECTED, COLOR_WHITE, fg_color);
        Sleep(150);

        now = next;
    }
    return;
}

void printElem(int board[][MAXSIZE],coord size,coord pos, coord board_offset,ball_type type) {
    switch (type) {
    case normal:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_BALL, COLOR_WHITE, board[pos.r][pos.c]+7);
        break;
    case selected:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_SELECTED, COLOR_WHITE, board[pos.r][pos.c]+7);
        break;
    case box:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_BOX, board[pos.r][pos.c] + 7, COLOR_BLACK);
        break;
    case normal_with_box:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_BALL_IN_BOX, board[pos.r][pos.c] + 7, COLOR_BLACK);
        break;
    case selected_with_box:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_SEL_BALL_IN_BOX, board[pos.r][pos.c] + 7, COLOR_BLACK);
        break;
    case none:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_BLANK, COLOR_WHITE, COLOR_WHITE);
        break;
    case deleted:
        showstr(pos.x * 4 + board_offset.x + 2, pos.y * 2 + board_offset.y + 1, PAT_DELETED, board[pos.r][pos.c] + 7, COLOR_WHITE);
        break;
    }
    return;
}
bool game_over(int (*board)[MAXSIZE], coord size)
{
    int space = 0;
    for (int i = 0; i < size.r; i++)
        for (int j = 0; j < size.c; j++)
            if (board[i][j] == 0)
                space++;
    return space <= 3;
}

int canclear(int (*board)[MAXSIZE], coord size, coord pos, coord *clear_set)
{
    int step[4][2] = {-1, 0, -1, 1, 0, 1, 1, 1};
    int this_ball = board[pos.r][pos.c];
    coord cat;
    int count, clear_count = 0;
    coord tmp[8];
    int dirs = -1;//交叉修正

    for (int d = 0; d < 4; d++)
    {
        count = 0;
        cat.r = pos.r + step[d][0];
        cat.c = pos.c + step[d][1];
        while (cat.r >= 0 && cat.r < size.r && cat.c >= 0 && cat.c < size.c && board[cat.r][cat.c] == this_ball)
        {
            tmp[count].r = cat.r;
            tmp[count++].c = cat.c;
            cat.r += step[d][0];
            cat.c += step[d][1];
        }

        cat.r = pos.r - step[d][0];
        cat.c = pos.c - step[d][1];
        while (cat.r >= 0 && cat.r < size.r && cat.c >= 0 && cat.c < size.c && board[cat.r][cat.c] == this_ball)
        {
            tmp[count].r = cat.r;
            tmp[count++].c = cat.c;
            cat.r -= step[d][0];
            cat.c -= step[d][1];
        }

        if (count >= 4)
        {
            if (clear_set != NULL)
                for (int i = 0; i < count; i++)
                {
                    clear_set->r = tmp[i].r;
                    clear_set->c = tmp[i].c;
                    clear_set++;
                }
            clear_count += count+1;
            dirs++;
        }
    }
    if (clear_count == 0) {
        if (clear_set != NULL)
            *clear_set = { -1,-1 }; 
        return 0;
    }
    else {
        if (clear_set != NULL)
            *clear_set++ = pos;
            *clear_set = { -1,-1 };
        return clear_count - dirs;
    }
}

int generate(int (*board)[MAXSIZE], coord size, int count)
{
    coord pos;
    int total = count;
    int try_times = 100;
    if (count > size.r * size.c)
        count = size.r * size.c;
    while (count)
    {
        pos.r = rand() % size.r;
        pos.c = rand() % size.c;
        if (board[pos.r][pos.c] == 0)
        {
            board[pos.r][pos.c] = rand() % 7 + 1;
            if (!canclear(board, size, pos, NULL))//不能消除,可以
                count--;
            else
                board[pos.r][pos.c] = 0;
        }
        if (try_times-- < 0)
            break;
    }
    return total - count;
}

int insert(int (*board)[MAXSIZE], coord size, int ball)
{
    bool block[MAXSIZE][MAXSIZE] = {0};
    for (int i = 0; i < size.r; i++) {
        for (int j = 0; j < size.c; j++) {
            if (board[i][j])block[i][j] = true;
        }
    }
    coord now;
    bool full = false;
    while (1)
    {
        now.r = rand() % size.r;
        now.c = rand() % size.c;
        if (!block[now.r][now.c]) {//能选or没试过
            if (board[now.r][now.c] == 0)//是空的
            {
                board[now.r][now.c] = ball;//尝试插入
                if (canclear(board, size, now, NULL))
                {//如果插入会导致清除,取消这次选择
                    block[now.r][now.c] = true;
                    board[now.r][now.c] = 0;
                }
                else//成功
                    break;
            }
            else {//非空
                block[now.r][now.c] = true;
                continue;
            }
        }//不能选
        //没成功,统计一下空格数
        full = true;
        for (int i = 0; i < size.r; i++) {
            for (int j = 0; j < size.c; j++) {
                if (block[i][j] == false) {
                    full = false;
                    i = j = MAXSIZE;
                }
            }
        }
        if (full) break;
    }
    return full ==false;
}

void print_board(int (*board)[MAXSIZE], coord size)
{
    printf("  |");
    for (int j = 0; j < size.c; j++)
        printf("  %d", j + 1);
    cout << endl;
    cout << "--+-";
    for (int j = 0; j < size.c; j++)
        cout << "---";
    cout << endl;
    for (int i = 0; i < size.r; i++)
    {
        cout << char(i + 'A') << " |";
        for (int j = 0; j < size.c; j++)
        {
            cout << "  ";
            if (board[i][j] != 0)
                setcolor(COLOR_HYELLOW, board[i][j]);
            cout << board[i][j];
            setcolor();
        }
        cout << endl;
    }
}

void paint_board(int (*board)[MAXSIZE], coord size)
{
    coord con_size, con_buf_size;

    setfontsize("新宋体", 32);
    setconsoleborder(size.x * 4 + 5, size.y * 4 + 5);
    setcursor(CURSOR_INVISIBLE);

    getconsoleborder(con_size.x, con_size.y, con_buf_size.x, con_buf_size.y);
    printf("屏幕：%d行%d列\n", con_buf_size.r, con_buf_size.c);

    setcolor(COLOR_WHITE, COLOR_BLACK);
    cout << "╔";
    for (int j = 0; j < size.x; j++)
        cout << "═";
    cout << "╗";

    for (int i = 0; i < size.y; i++)
    {
        showstr(0, i + 2, "║", COLOR_WHITE, COLOR_BLACK);
        showstr(size.x * 2 + 2, i + 2, "║", COLOR_WHITE, COLOR_BLACK);
    }

    setcolor(COLOR_WHITE, COLOR_BLACK);
    gotoxy(0, size.y + 2);
    cout << "╚";
    for (int j = 0; j < size.x; j++)
        cout << "═";
    cout << "╝";

    for (int i = 0; i < size.y; i++)
    {
        gotoxy(2, i + 2);
        for (int j = 0; j < size.x; j++)
        {
            if (board[i][j] != 0)
                setcolor(board[i][j] + 7, COLOR_WHITE);
            else
                setcolor(COLOR_WHITE, COLOR_WHITE);
            cout << PAT_BALL;
        }
    }
    return;
}

void paint_board_with_line(int (*board)[MAXSIZE], coord size, coord offset,bool update)
{
    if (!update)
    {
        setcolor(COLOR_WHITE, COLOR_BLACK);
        gotoxy(offset.x, offset.y);
        cout << "╔";
        for (int j = 1; j < size.x; j++)
            cout << "═╦";
        cout << "═╗";

        for (int i = 1; i <= size.r; i++)
        {
            gotoxy(offset.x, offset.y + i * 2 - 1);
            cout << "║";
            for (int j = 0; j < size.c; j++)
                cout << PAT_BLANK << "║";
            gotoxy(offset.x, offset.y + i * 2);
            if (i != size.y)
            {
                cout << "╠";
                for (int j = 1; j < size.c; j++)
                    cout << "═╬";
                cout << "═╣";
            }
            else
            {
                cout << "╚";
                for (int j = 1; j < size.c; j++)
                    cout << "═╩";
                cout << "═╝";
            }
        }
    }
    for (int y = 0; y < size.y; y++)
    {
        for (int x = 0; x < size.x; x++)
        {
            if (board[y][x] != 0)
                printElem(board, size, { y,x }, offset, normal);
            else
                printElem(board, size, { y,x }, offset, none);
        }
    }
    return;
}

void paint_score(int score, coord offset,bool update)
{
    setcolor(COLOR_WHITE, COLOR_BLACK);
    if (!update)
    {
        gotoxy(offset.x, offset.y);
        cout << "╔═════╗";
        gotoxy(offset.x, offset.y+1);
        cout << "║得分：    ║"; 
        gotoxy(offset.x, offset.y + 2);
        cout << "╚═════╝";
    }

    gotoxy(offset.x + 8, offset.y + 1);
    printf("%-4d", score);
    return;
}

void paint_next(int *next, coord offset,bool update)
{
    setcolor(COLOR_WHITE, COLOR_BLACK);
    if (!update)
    {
        gotoxy(offset.x, offset.y);
        cout << "╔═╦═╦═╗";
        gotoxy(offset.x, offset.y + 1);
        printf("║" PAT_BLANK "║" PAT_BLANK "║" PAT_BLANK "║");
        gotoxy(offset.x, offset.y + 2);
        cout << "╚═╩═╩═╝";
    }
    showstr(offset.x + 2, offset.y + 1, PAT_BALL, COLOR_WHITE, next[0] + 7);
    showstr(offset.x + 6, offset.y + 1, PAT_BALL, COLOR_WHITE, next[1] + 7);
    showstr(offset.x + 10, offset.y + 1, PAT_BALL, COLOR_WHITE, next[2] + 7);

    return;
}

void paint_stat(int (*board)[MAXSIZE], coord size, coord offset, int clear_count[8],bool update)
{
    int stat[8] = {0};
    int total = size.r * size.c;
    static int clear_count_total[8] = {0};

    for (int i = 0; i < size.y; i++)
        for (int j = 0; j < size.x; j++)
            stat[board[i][j]]++;

    if (!update)
    {
        showstr(offset.x, offset.y, "╔═════════╗", COLOR_WHITE, COLOR_BLACK);
        for (int i = 0; i < 8; i++)
        {
            showstr(offset.x + 2, offset.y + i + 1, PAT_BALL, COLOR_WHITE, i + 7);
            showstr(offset.x, offset.y + i + 1, "║", COLOR_WHITE, COLOR_BLACK);
            showstr(offset.x + 20, offset.y + i + 1, "║", COLOR_WHITE, COLOR_BLACK);
        }
        showstr(offset.x, offset.y + 9, "╚═════════╝", COLOR_WHITE, COLOR_BLACK);
    }
    for (int i = 0; i < 8; i++)
    {
        setcolor(COLOR_WHITE, COLOR_BLACK);
        gotoxy(offset.x + 4, offset.y + i + 1);
        clear_count_total[i] += clear_count[i];
        printf(":%02d/%2d%% del-%-4d", stat[i], 100 * stat[i] / total, clear_count_total[i]);
    }
    return;
}
