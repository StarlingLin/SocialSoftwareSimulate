// AdminMenuLX.cpp
#include "AdminMenuLX.h"
#include <iostream>

using namespace std;

// 显示后台管理主菜单
void AdminMenuLX::showMainMenu()
{
    int choice = -1;
    pageStack.push(0); // 主菜单页面编号为 0

    while (!pageStack.empty())
    {
        int currentPage = pageStack.top();

        switch (currentPage)
        {
        case 0: // 主菜单
            cout << "\n--- 后台管理主菜单 ---\n";
            cout << "1. 用户管理\n2. 群组管理\n3. 服务管理\n4. 消息管理\n5. 退出\n";
            choice = getUserInput();

            if (choice == 1) navigateTo(1);
            else if (choice == 2) navigateTo(2);
            else if (choice == 3) navigateTo(3);
            else if (choice == 4) navigateTo(4);
            else if (choice == 5) goBack();
            break;

        case 1: // 用户管理菜单
            userManagementMenu();
            break;

        case 2: // 群组管理菜单
            groupManagementMenu();
            break;

        case 3: // 服务管理菜单
            serviceManagementMenu();
            break;

        case 4: // 消息管理菜单
            messageManagementMenu();
            break;
        }
    }
}

// 用户管理菜单
void AdminMenuLX::userManagementMenu()
{
    cout << "\n--- 用户管理 ---\n";
    cout << "功能未实现\n";
    goBack();
}

// 群组管理菜单
void AdminMenuLX::groupManagementMenu()
{
    cout << "\n--- 群组管理 ---\n";
    cout << "功能未实现\n";
    goBack();
}

// 服务管理菜单
void AdminMenuLX::serviceManagementMenu()
{
    cout << "\n--- 服务管理 ---\n";
    cout << "功能未实现\n";
    goBack();
}

// 消息管理菜单
void AdminMenuLX::messageManagementMenu()
{
    cout << "\n--- 消息管理 ---\n";
    cout << "功能未实现\n";
    goBack();
}

// 导航到指定页面
void AdminMenuLX::navigateTo(int pageID)
{
    system("cls");
    pageStack.push(pageID);
}

// 返回上一级页面
void AdminMenuLX::goBack()
{
    system("cls");
    if (!pageStack.empty())
    {
        pageStack.pop();
    }
    if (pageStack.empty())
    {
        cout << "\n已退出后台管理系统。\n";
        exit(0);
    }
}

// 辅助函数：处理用户输入
int AdminMenuLX::getUserInput()
{
    int choice;
    cout << "请输入选项：";
    cin >> choice;
    return choice;
}
