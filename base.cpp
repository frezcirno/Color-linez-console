#include "main.h"
#include <iostream>
#include <ctime>
#include "cmd_console_tools.h"
using namespace std;

void func1()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;
    coord now_cur;

    getRandC(size);

    srand((unsigned int)time(NULL));
    generate(board, size, 5);

    cls();
    cout << "初始数组：" << endl;
    print_board(board, size);
    cout << endl;

    cout << "本小题结束，请输入End继续...";
    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func2()
{
    coord size;
    int board[MAXSIZE][MAXSIZE] = { 0 };
    int next[3];

    coord start, end;
    coord now_cur;
    coord path[100];

    getRandC(size);

    srand((unsigned int)time(NULL));
    generate(board, size, size.r * size.c * 3 / 5);

    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    cls();
    cout << "当前数组：" << endl;
    print_board(board, size);
    printf("\n下3个彩球的颜色分别是：%d %d %d\n", next[0], next[1], next[2]);

    cout << "请以字母+数字形式[例：c2]输入要移动球的矩阵坐标：";
    while (1)
    {
        getxy(now_cur.x, now_cur.y);
        start.r = getchar();
        start.c = getchar();
        clearstdin();
        start.r = tolower(start.r) - 'a';
        start.c = start.c - '1';
        if (start.c < 0 || start.c >= size.c || start.r < 0 || start.r >= size.r)
        {
            showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
            gotoxy(now_cur.x, now_cur.y);
        }
        else if (board[start.r][start.c] == 0)
        {
            showstr(0, now_cur.y + 1, "起始位置为空，请重新输入.", 0, 7, 1, 30);
            gotoxy(now_cur.x, now_cur.y);
        }
        else
            break;
    }
    printf("输入为%c行%c列\n", start.r + 'A', start.c + '1');

    cout << "请以字母+数字形式[例：c2]输入要移动球的目的坐标：";
    while (1)
    {
        getxy(now_cur.x, now_cur.y);
        end.r = getchar();
        end.c = getchar();
        clearstdin();
        end.r = tolower(end.r) - 'a';
        end.c = end.c - '1';
        if (end.c < 0 || end.c >= size.c || end.r < 0 || end.r >= size.r)
        {
            showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
            gotoxy(now_cur.x, now_cur.y);
        }
        else if (board[end.r][end.c] != 0)
        {
            showstr(0, now_cur.y + 1, "目标位置非空，请重新输入.", 0, 7, 1, 30);
            gotoxy(now_cur.x, now_cur.y);
        }
        else if (!bfs(board, size, start, end, path))
        {
            showstr(0, now_cur.y + 1, "无法找到移动路径", 0, 7, 1, 30);
            gotoxy(now_cur.x, now_cur.y);
        }
        else
        {
            break;
        }
    }
    //路径图
    char tmp_map[MAXSIZE][MAXSIZE] = { 0 };
    coord*p = path;
    while (p->r != -1) 
        tmp_map[p->r][p++->c] = '*';

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
            if (tmp_map[i][j] != 0){
                setcolor(COLOR_HYELLOW, COLOR_GREEN);
            cout << tmp_map[i][j];
            }
            else {
                setcolor();
                cout << board[i][j];
            }
            setcolor();
        }
        cout << endl;
    }

    cout << endl;
    cout << "本小题结束，请输入End继续...";
    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func3()
{
    coord size;
    int board[MAXSIZE][MAXSIZE] = { 0 };
    int next[3];
    int score, total = 0;

    coord start, end;
    coord now_cur;
    int clear_count[8] = { 0 };

    coord *clear_set = NULL;

    getRandC(size);

    srand((unsigned int)time(NULL));
    generate(board, size, 5);

    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    cls();
    while (!game_over(board, size))
    {
        cout << "当前数组：" << endl;
        print_board(board, size);

        printf("\n下3个彩球的颜色分别是：%d %d %d\n", next[0], next[1], next[2]);

        cout << "请以字母+数字形式[例：c2]输入要移动球的矩阵坐标：";
        while (1)
        {
            getxy(now_cur.x, now_cur.y);
            start.r = getchar();
            start.c = getchar();
            clearstdin();
            start.r = tolower(start.r) - 'a';
            start.c = start.c - '1';
            if (start.c < 0 || start.c >= size.c || start.r < 0 || start.r >= size.r)
            {
                showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
                gotoxy(now_cur.x, now_cur.y);
            }
            else if (board[start.r][start.c] == 0)
            {
                showstr(0, now_cur.y + 1, "起始位置为空，请重新输入.", 0, 7, 1, 30);
                gotoxy(now_cur.x, now_cur.y);
            }
            else
                break;
        }
        printf("输入为%c行%c列               \n", start.r + 'A', start.c + '1');

        cout << "请以字母+数字形式[例：c2]输入要移动球的目的坐标：";
        while (1)
        {
            getxy(now_cur.x, now_cur.y);
            end.r = getchar();
            end.c = getchar();
            clearstdin();
            end.r = tolower(end.r) - 'a';
            end.c = end.c - '1';
            if (end.c < 0 || end.c >= size.c || end.r < 0 || end.r >= size.r)
            {
                showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
                gotoxy(now_cur.x, now_cur.y);
            }
            else if (board[end.r][end.c] != 0)
            {
                showstr(0, now_cur.y + 1, "目标位置非空，请重新输入.", 0, 7, 1, 30);
                gotoxy(now_cur.x, now_cur.y);
            }
            else if (!bfs(board, size, start, end, NULL))
            {
                showstr(0, now_cur.y + 1, "无法找到移动路径", 0, 7, 1, 30);
                gotoxy(now_cur.x, now_cur.y);
            }
            else
            {
                break;
            }
        }
        printf("输入为%c行%c列                \n", end.r + 'A', end.c + '1');

        board[end.r][end.c] = board[start.r][start.c];
        board[start.r][start.c] = 0;

        if (canclear(board, size, end, clear_set))
        {
            clear(board, clear_set, clear_count);
            score = get_score(clear_count);
            total += score;
        }
        else
        {
            score = 0;
            insert(board, size, next[0]);
            insert(board, size, next[1]);
            insert(board, size, next[2]);
            next[0] = rand() % 7 + 1;
            next[1] = rand() % 7 + 1;
            next[2] = rand() % 7 + 1;
        }
        cout << endl;
        printf("本次得分：%d 总得分：%d\n\n\n", score, total);
    }
    cout << "无空位可移动，游戏结束!" << endl;

    cout << endl;
    cout << "本小题结束，请输入End继续...";
    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "输入错误，请重新输入.", 0, 7, 1, 30);
        gotoxy(now_cur.x, now_cur.y);
    }
}