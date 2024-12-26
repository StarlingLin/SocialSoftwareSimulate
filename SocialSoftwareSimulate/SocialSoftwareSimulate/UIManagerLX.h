#pragma once

#include <stack>
#include <string>
#include <iostream>
#include "LoggerLX.h"
#include "ManagerLX.h"
#include "DatabaseLX.h"

using namespace std;

class UIManagerLX
{
private:
    stack<string> pageStack;          // 页面栈，用于管理界面切换
    LoggerLX* logger;                 // 日志管理器
    UserManagerLX* userManager;       // 用户管理器
    ServiceManagerLX* serviceManager; // 服务管理器
    GroupManagerLX* groupManager;     // 群组管理器
    DatabaseLX* database;             // 数据库管理器

    string currentService;            // 当前进入的服务名称
    string loggedInUser;              // 当前登录的用户名

    void displayMainMenu();           // 显示主菜单
    void displayLoginMenu();          // 显示登录界面
    void displayRegisterMenu();       // 显示注册界面
    void displayServiceSelectionMenu(); // 显示服务选择菜单
    void displayServiceMenu();        // 显示服务菜单
    void displayUserManagementMenu(); // 显示用户管理菜单
    void displayGroupManagementMenu();// 显示群组管理菜单

public:
    UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database);

    void start();                     // 启动界面管理器
};
