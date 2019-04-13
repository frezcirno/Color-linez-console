#pragma once

#include <Windows.h>

/* 定义颜色（用宏定义取代数字，方便记忆） */
#define COLOR_BLACK		0	//黑
#define COLOR_BLUE		1	//蓝
#define COLOR_GREEN		2	//绿
#define COLOR_CYAN		3	//青
#define COLOR_RED		4	//红
#define COLOR_PINK		5	//粉
#define COLOR_YELLOW	6	//黄
#define COLOR_WHITE		7	//白
#define COLOR_HBLACK	8	//亮黑
#define COLOR_HBLUE		9	//亮蓝
#define COLOR_HGREEN	10	//亮绿
#define COLOR_HCYAN		11	//亮青
#define COLOR_HRED		12	//亮红
#define COLOR_HPINK		13	//亮粉
#define COLOR_HYELLOW	14	//亮黄
#define COLOR_HWHITE	15	//亮白

/* 定义鼠标键盘操作类型 */
#define CCT_MOUSE_EVENT				0
#define CCT_KEYBOARD_EVENT			1

/* 定义四个方向键 */
#define KB_ARROW_UP					72
#define KB_ARROW_DOWN				80
#define KB_ARROW_LEFT				75
#define KB_ARROW_RIGHT				77

/* 定义鼠标的操作 */
#define MOUSE_NO_ACTION						0x0000	//无鼠标操作
#define MOUSE_ONLY_MOVED						0x0001	//鼠标移动
#define MOUSE_LEFT_BUTTON_CLICK				0x0002	//按下左键
#define MOUSE_LEFT_BUTTON_DOUBLE_CLICK		0x0004	//双击左键
#define MOUSE_RIGHT_BUTTON_CLICK				0x0008	//按下右键
#define MOUSE_RIGHT_BUTTON_DOUBLE_CLICK		0x0010	//双击右键
#define MOUSE_LEFTRIGHT_BUTTON_CLICK			0x0020	//同时按下左右键
#define MOUSE_WHEEL_CLICK					0x0040	//滚轮被按下
#define MOUSE_WHEEL_MOVED_UP					0x0080	//滚轮向上移动
#define MOUSE_WHEEL_MOVED_DOWN				0x0100	//滚轮向下移动

/* 定义光标的形态 */
#define CURSOR_VISIBLE_FULL			0	//光标显示，全高色块
#define CURSOR_VISIBLE_HALF			1	//光标显示，半高色块
#define CURSOR_VISIBLE_NORMAL		2	//光标显示，横线（缺省为此方式）
#define CURSOR_INVISIBLE				3	//光标不显示

/* cmd_console_tools下的函数声明 */

/* 清屏、颜色设置、光标设置、字符/字符串显示 */
void cls      (void);
void setcolor (const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE);
void getcolor (int &bg_color, int &fg_color);
void gotoxy   (const int X, const int Y);
void getxy    (int &x, int &y);
void setcursor(const int options);
void showch   (const int X, const int Y, const char ch, const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE, const int rpt = 1);
void showstr  (const int X, const int Y, const char *str, const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE, int rpt = 1, int max_len=-1);
void showint  (const int X, const int Y, const int num, const int bg_color = COLOR_BLACK, const int fg_color = COLOR_WHITE, const int rpt = 1);

/* 与窗口大小有关的函数 */
void setconsoleborder(int set_cols, int set_lines, int set_buffer_cols = -1, int set_buffer_lines = -1);
void getconsoleborder(int &cols, int &lines, int &buffer_cols, int &buffer_lines);

/* 有标题栏有关的函数 */
void getconsoletitle (char *title, int maxbuflen);
void setconsoletitle (const char *title);

/* 与鼠标操作有关的函数 */
void enable_mouse           (void);
void disable_mouse          (void);
int  read_keyboard_and_mouse(int &MX, int &MY, int &MAction, int &keycode1, int &keycode2);

/* 与字体及字号设置有关的函数 */
int  getfontinfo(void);
void setfontsize(const char *fontname, const int high, const int width = 0);

