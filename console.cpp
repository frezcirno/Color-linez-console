#include "main.h"
#include "cmd_console_tools.h"
#include <ctime>
#include <iostream>
using namespace std;
void clearstdin()
{
    char c;
    while ((c = getchar()) != EOF && c != '\n')
        ;
}

void func4()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;
    coord now_cur;

    srand((unsigned int)time(NULL));
    getRandC(size);
    generate(board, size, 5);

    paint_board(board, size);

    showstr(0,size.y+4,"本小题结束，请输入End继续...");

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

void func5()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur;
    coord con_size, con_buf_size;

    int score = 0, total = 0, clear_count[8] = { 0 };

    getRandC(size);

    srand((unsigned int)time(NULL));
    generate(board, size, 5);

    setconsoleborder(size.c * 4 + 7, size.r * 2 + 5);
    setcursor(CURSOR_INVISIBLE);
    getconsoleborder(con_size.r, con_size.c, con_buf_size.r, con_buf_size.c);
    printf("屏幕：%d行%d列\n", con_buf_size.r, con_buf_size.c);
    paint_board_with_line(board, size, { 1, 0}, 0);

    showstr(0, size.y * 2 + 2, "本小题结束，请输入End继续...");
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

void func6()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;
    coord start, end, now;

    coord now_cur, con_size, con_buf_size;

    int clear_count[8] = { 0 };

    int loop, valid, ret, X, Y, maction, keycode1, keycode2;

    int next[3];

    coord path[100];
    coord clear_set[50];

    srand((unsigned int)time(NULL));
    getRandC(size);

    generate(board, size, size.r * size.c * 3 / 5);

    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 3, 2 * size.r + 5);
    setfontsize("新宋体", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.r, con_buf_size.c);

    cls();
    printf("屏幕：%d行%d列(右键退出)", con_buf_size.r, con_buf_size.c);
    paint_board_with_line(board, size, { 1, 0 }, 0);

    enable_mouse();
    start = { -1,-1 };
    loop = 1;
    while (loop)
    {
        ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

        if (ret == CCT_MOUSE_EVENT)
        {
            now = { Y - 1,(X - 0) / 2 };

            //检查输入位置
            valid = 0;
            if (now.x % 2 == 1 && now.y % 2 == 1)
            {
                now.x /= 2;
                now.y /= 2;
                if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                    valid = 1;
            }

            //有效,显示
            if (valid)
            {
                gotoxy(0, 2 * size.r + 2);
                setcolor();
                printf("[当前鼠标] %c行%c列                       ", now.r + 'A', now.c + '1');

                if (maction == MOUSE_LEFT_BUTTON_CLICK) //按下左键
                {
                    showstr(0, 2 * size.r + 2, "[[点击]]");

                    if ((start.x == X && start.y == Y))
                        break;
                   
                    if (board[now.r][now.c] != 0) //有球,重选起始球
                    {
                        if (start.x != -1) //将原来选中位置的球复原
                            printElem(board, size, start, {1,0 }, normal);
                        start = now; 
                        printElem(board, size, start, {1,0}, selected);
                    }
                    else if (start.x != -1 && start.y != -1) //没球,且已选起始球
                    {
                        end = now;
                        if (!bfs(board, size, start, end, path))
                        {
                            gotoxy(0, 2 * size.r + 2);
                            setcolor();
                            printf("[错误] 无法从[%c%c]移动到[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                        }
                        else
                        { //可以移动
                            dmove(board, size, { 1,0 }, path);

                            board[end.r][end.c] = board[start.r][start.c];
                            board[start.r][start.c] = 0;
                            start = { -1, -1 };

                            if (canclear(board, size, start, clear_set))
                            {
                                dclear(board, size, { 1,0 }, clear_set);
                                clear(board, clear_set, clear_count);
                            }
                            else
                            {
                                insert(board, size, next[0]);
                                insert(board, size, next[1]);
                                insert(board, size, next[2]);
                                next[0] = rand() % 7 + 1;
                                next[1] = rand() % 7 + 1;
                                next[2] = rand() % 7 + 1;
                            }
                            break;
                        }
                    } //点击空位置...

                } //maction
            }     //if valid
            //按了右键
            if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                break;
        }     //(CCT_MOUSE_EVENT)
    }         //end of while(loop)

    disable_mouse(); //禁用鼠标

    showstr(0, size.r * 2 + 3, "本小题结束，请输入End继续...");
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

void func7()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur;
    coord con_size, con_buf_size;

    coord start, end, now;
    int next[3];
    coord path[100];
    coord clear_set[50];
    int score = 0, total = 0, clear_count[8] = { 0 };
    int loop, wait_input, valid, ret, X, Y, maction, keycode1, keycode2;

    

    srand((unsigned int)time(NULL));
    getRandC(size);

    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 50, 2 * size.r + 10);
    setfontsize("新宋体", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.x, con_buf_size.y);

    enable_mouse();
    cls();

    generate(board, size, 5);
    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    printf("屏幕：%d行%d列(右键退出)", con_buf_size.r, con_buf_size.c);

    coord board_start = { 1, 0 }; //size.r/y,size.c/x
    coord score_start = { 1, size.x * 4 + 12 };
    coord next_start = { 5, size.x * 4 + 12 };
    coord stat_start = { 9, size.x * 4 + 12 };
    coord tips_start = { 2 * size.r + 2, 0 };

    paint_board_with_line(board, size, board_start, 0);
    paint_score(total, score_start, 0);
    paint_next(next, next_start, 0);
    paint_stat(board, size, stat_start, clear_count, 0);

    start = { -1,-1 };
    loop = 1;
    while (!game_over(board, size) && loop)
    {
        paint_board_with_line(board, size, board_start, 1);
        paint_score(total, score_start, 1);
        paint_next(next, next_start, 1);
        paint_stat(board, size, stat_start, clear_count, 1);

        wait_input = 1;
        while (wait_input)
        {
            ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

            if (ret == CCT_MOUSE_EVENT)
            {
                now.x = (X - board_start.x) / 2;
                now.y = Y - board_start.y;

                //检查输入位置
                valid = 0;
                if (now.x % 2 == 1 && now.y % 2 == 1)
                {
                    now.x /= 2;
                    now.y /= 2;
                    if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                        valid = 1;
                }
                //有效,显示
                if (valid)
                {
                    gotoxy(tips_start.x, tips_start.y);
                    setcolor();
                    printf("[当前鼠标] %c行%c列                       ", now.r + 'A', now.c + '1');

                    if (maction == MOUSE_LEFT_BUTTON_CLICK) //按下左键
                    {
                        showstr(tips_start.x+1, tips_start.y, "[[点击]]");

                        if (board[now.r][now.c] != 0) //有球,重选起始球
                        {
                            if (start.x != -1) //将原来选中位置的球复原
                                printElem(board, size, start, board_start, normal);
                            start = now;
                            printElem(board, size, now, board_start, selected);
                        }
                        else if (start.x != -1 && start.y != -1) //没球,且已选起始球
                        {
                            end = now;
                            if (!bfs(board, size, start, end, path))
                            {
                                gotoxy(tips_start.x, tips_start.y);
                                setcolor();
                                printf("[错误] 无法从[%c%c]移动到[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                            }
                            else
                            { //可以移动
                                dmove(board, size, board_start, path);

                                board[end.r][end.c] = board[start.r][start.c];
                                board[start.r][start.c] = 0;
                                start = { -1, -1 };

                                if (canclear(board, size, end, clear_set))
                                {
                                    dclear(board, size, board_start, clear_set);
                                    clear(board, clear_set, clear_count);
                                }
                                else
                                {
                                    insert(board, size, next[0]);
                                    insert(board, size, next[1]);
                                    insert(board, size, next[2]);
                                    next[0] = rand() % 7 + 1;
                                    next[1] = rand() % 7 + 1;
                                    next[2] = rand() % 7 + 1;
                                }
                                wait_input = 0;
                            }
                        } //点击空位置...

                    } //maction
                }     //if valid
                //按了右键
                if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    loop = wait_input = 0;
            } //if (CCT_MOUSE_EVENT)
        }     //loop
    }         //!gameover&&loop

    disable_mouse(); //禁用鼠标

    showstr(tips_start.x, tips_start.y + 2, "本小题结束，请输入End继续...");

    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "输入错误，请重新输入.");
        gotoxy(now_cur.x, now_cur.y);
    }
}

void func8()
{
    int board[MAXSIZE][MAXSIZE] = { 0 };
    coord size;

    coord now_cur, con_size, con_buf_size;

    coord start, end, now, selectbox;
    int next[3];
    coord path[100];
    coord clear_set[50];
    int score = 0, total = 0, clear_count[8] = { 0 };
    int loop, wait_input, valid, ret, X, Y, maction, keycode1, keycode2;

    getRandC(size);

    srand((unsigned int)time(NULL));
    setcursor(CURSOR_INVISIBLE);
    setconsoleborder(4 * size.c + 50, 2 * size.r + 10);
    setfontsize("新宋体", 28);
    getconsoleborder(con_size.x, con_size.y, con_buf_size.x, con_buf_size.y);
    enable_mouse();

    generate(board, size, 5);
    next[0] = rand() % 7 + 1;
    next[1] = rand() % 7 + 1;
    next[2] = rand() % 7 + 1;

    //各个打印框位置
    coord board_start = { 1, 0 }; //size.r/y,size.c/x
    coord score_start = { 1, size.x * 4 + 12 };
    coord next_start = { 5, size.x * 4 + 12 };
    coord stat_start = { 9, size.x * 4 + 12 };
    coord tips_start = { 2 * size.r + 2, 0 };
    start = { -1,-1 };
    selectbox = { 0,0 };//初始位置为{0,0}

    cls();
    printf("屏幕：%d行%d列(右键退出)", con_buf_size.r, con_buf_size.c);

    paint_board_with_line(board, size, board_start, 0);
    paint_score(total, score_start, 0);
    paint_next(next, next_start, 0);
    paint_stat(board, size, stat_start, clear_count, 0);

    loop = 1;
    while (!game_over(board, size) && loop)
    {
        paint_board_with_line(board, size, board_start, 1);
        paint_score(total, score_start, 1);
        paint_next(next, next_start, 1);
        paint_stat(board, size, stat_start, clear_count, 1);
        printElem(board, size, selectbox, board_start, board[selectbox.r][selectbox.c] ? normal_with_box : box);

        wait_input = 1;
        while (wait_input)
        {
            ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);

            if (ret == CCT_MOUSE_EVENT)
            {
                now.x = (X - board_start.x) / 2;
                now.y = Y - board_start.y;

                //检查输入位置
                valid = 0;
                if (now.x % 2 == 1 && now.y % 2 == 1)
                {
                    now.x /= 2;
                    now.y /= 2;
                    if (now.x >= 0 && now.x < size.x && now.y >= 0 && now.y < size.y)
                        valid = 1;
                }
                //有效,显示
                if (valid)
                {
                    gotoxy(tips_start.x, tips_start.y);
                    setcolor();
                    printf("[当前鼠标] %c行%c列                       ", now.r + 'A', now.c + '1');

                    if (maction == MOUSE_LEFT_BUTTON_CLICK) //按下左键
                    {
                        showstr(tips_start.x + 1, tips_start.y, "[[点击]]");

                        if (board[now.r][now.c] != 0) //有球,重选起始球
                        {
                            if (start.x != -1) //将原来选中位置的球复原
                                printElem(board, size, start, board_start, normal);
                            start = now;
                            printElem(board, size, now, board_start, selected);
                        }
                        else if (start.x != -1 && start.y != -1) //没球,且已选起始球
                        {
                            end = now;
                            if (!bfs(board, size, start, end, path))
                            {
                                gotoxy(tips_start.x, tips_start.y);
                                setcolor();
                                printf("[错误] 无法从[%c%c]移动到[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                            }
                            else
                            { //可以移动
                                dmove(board, size, board_start, path);

                                board[end.r][end.c] = board[start.r][start.c];
                                board[start.r][start.c] = 0;
                                start = { -1, -1 };

                                if (canclear(board, size, end, clear_set))
                                {
                                    dclear(board, size, board_start, clear_set);
                                    clear(board, clear_set, clear_count);
                                }
                                else
                                {
                                    insert(board, size, next[0]);
                                    insert(board, size, next[1]);
                                    insert(board, size, next[2]);
                                    next[0] = rand() % 7 + 1;
                                    next[1] = rand() % 7 + 1;
                                    next[2] = rand() % 7 + 1;
                                }
                                wait_input = 0;
                            }
                        } //点击空位置...

                    } //maction
                }     //if valid
                //按了右键
                if (maction == MOUSE_RIGHT_BUTTON_CLICK)
                    loop = wait_input = 0;

            } //if (CCT_MOUSE_EVENT)
            else if (ret == CCT_KEYBOARD_EVENT) {
                showstr(tips_start.x, tips_start.y, "[当前按键]                       ", 0, 7, 1, 30);
                
                switch (keycode1) {
                case 27:	//ESC键,取消选择
                    if(start.x!=-1)
                        printElem(board, size, start, board_start,normal );
                    start = { -1,-1 };
                    showstr(tips_start.x + 10, tips_start.y, "Esc", 0, 7, 1, 30);
                    break;//Esc break
                case 13://Enter
                case 32://Space
                    if (board[selectbox.r][selectbox.c] != 0) //有球,重选起始球
                    {
                        if (start.x != -1) //将原来选中位置的球复原
                            printElem(board, size, start, board_start, normal);
                        start = selectbox;
                        printElem(board, size, start, board_start, selected_with_box);
                    }
                    else if (start.x != -1) //没球,且已选起始球
                    {
                        end = selectbox;
                        if (!bfs(board, size, start, end, path))
                        {
                            gotoxy(tips_start.x, tips_start.y);
                            setcolor();
                            printf("[错误] 无法从[%c%c]移动到[%c%c]", start.x + 'A', start.y + '1', end.x + 'A', end.y + '1');
                        }
                        else
                        { //可以移动
                            dmove(board, size, board_start, path);

                            board[end.r][end.c] = board[start.r][start.c];
                            board[start.r][start.c] = 0;
                            start = { -1, -1 };//重置start位置

                            if (canclear(board, size, end, clear_set))
                            {
                                dclear(board, size, board_start, clear_set);
                                clear(board, clear_set, clear_count);
                            }
                            else
                            {
                                insert(board, size, next[0]);
                                insert(board, size, next[1]);
                                insert(board, size, next[2]);
                                next[0] = rand() % 7 + 1;
                                next[1] = rand() % 7 + 1;
                                next[2] = rand() % 7 + 1;
                            }
                            wait_input = 0;
                        }
                    } 
                    break;//Enter break
                case 224://方向键
                    //原位置
                    if(selectbox.x==start.x&&selectbox.y==start.y)//是选中的
                        printElem(board, size, selectbox, board_start, selected);
                    else//不是
                        printElem(board, size,selectbox , board_start, normal);
                        switch (keycode2) {
                    case KB_ARROW_UP:
                        if(selectbox.y>0)selectbox.y--;
                        showstr(tips_start.x+10, tips_start.y, "上箭头", 0, 7, 1, 30);
                        break;
                    case KB_ARROW_DOWN:
                        if (selectbox.y <size.y-1)selectbox.y++;
                        showstr(tips_start.x + 10, tips_start.y, "下箭头", 0, 7, 1, 30); 
                        break;
                    case KB_ARROW_LEFT:
                        if (selectbox.x > 0)selectbox.x--;
                        showstr(tips_start.x + 10, tips_start.y, "左箭头", 0, 7, 1, 30);
                        break;
                    case KB_ARROW_RIGHT:
                        if (selectbox.x <size.x-1)selectbox.x++;
                        showstr(tips_start.x + 10, tips_start.y, "右箭头", 0, 7, 1, 30);
                        break;
                    }//四个方向
                    //新位置
                        if (selectbox.r == start.r&&selectbox.c == start.c)//是选中的
                            printElem(board, size, selectbox, board_start, selected_with_box);
                        else if (board[selectbox.r][selectbox.c] != 0)
                            printElem(board, size, selectbox, board_start, normal_with_box);
                        else
                            printElem(board, size, selectbox, board_start, box);
                     break;//case 224 break
                }//end of swicth(keycode1)
            }//end of else if(ret == CCT_KEYBOARD_EVENT）

        }     //loop
    }         //!gameover&&loop

    disable_mouse(); //禁用鼠标

    showstr(tips_start.x, tips_start.y + 2, "本小题结束，请输入End继续...");

    getxy(now_cur.x, now_cur.y);
    while (1)
    {
        if (getchar() == 'E' && getchar() == 'n' && getchar() == 'd')
            break;
        clearstdin();
        showstr(0, now_cur.y + 1, "输入错误，请重新输入.");
        gotoxy(now_cur.x, now_cur.y);
    }
}