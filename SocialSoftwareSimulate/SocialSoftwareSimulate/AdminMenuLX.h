#pragma once

#include <stack>

using namespace std;

class AdminMenuLX
{
private:
    stack<int> pageStack; // 页面栈，用于管理菜单导航

public:
    // 显示后台管理主菜单
    void showMainMenu();

    // 用户管理菜单
    void userManagementMenu();

    // 群组管理菜单
    void groupManagementMenu();

    // 服务管理菜单
    void serviceManagementMenu();

    // 消息管理菜单
    void messageManagementMenu();

    // 导航到指定页面
    void navigateTo(int pageID);

    // 返回上一级页面
    void goBack();

    // 辅助函数：处理用户输入
    int getUserInput();
};
