#include "main.h"
#include <iostream>
#include "cmd_console_tools.h"
#include <conio.h>
using namespace std;

void start_page()
{
    
}
int main(int argc, char const *argv[])
{
    int cont = 1;
    setconsoleborder(80, 25);
    while (cont)
    {
        setcolor();
        setconsoleborder(80, 25);
        cls();
        cout << "---------------------------------------------" << endl;
        cout << "1.内部数组，随机生成初始5个球" << endl;
        cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
        cout << "3.内部数组，完整版" << endl;
        cout << "4.画出n*n的框架（无分隔线），随机显示5个球" << endl;
        cout << "5.画出n*n的框架（有分隔线），随机显示5个球" << endl;
        cout << "6.n*n的框架，60%的球，支持鼠标，完成一次移动" << endl;
        cout << "7.cmd图形界面完整版" << endl;
        cout << "8.cmd图形界面完整版-支持同时读键（额外加分）" << endl;
        cout << "0.退出" << endl;
        cout << "---------------------------------------------" << endl;
        cout << "[请选择0-8]" << endl;

        switch (_getch())
        {
        case '1':
            func1();
            break;
        case '2':
            func2();
            break;
        case '3':
            func3();
            break;
        case '4':
            func4();
            break;
        case '5':
            func5();
            break;
        case '6':
            func6();
            break;
        case '7':
            func7();
            break;
        case '8':
            func8();
            break;
        case '0':
            cont = 0;
            break;
        default:
            continue;
        }
    }
    return 0;
}