#pragma once

#include <string>
#include <iostream>
#include "ManagerLX.h"
#include "DatabaseLX.h"
#include "LoggerLX.h"

using namespace std;

class CommunicationSystemLX 
{
private:
    UserManagerLX userManager;        // 用户管理器
    GroupManagerLX* groupManager;    // 群组管理器基类指针
    ServiceManagerLX* serviceManager; // 服务管理器基类指针
    DatabaseLX database;             // 数据库
    LoggerLX logger;                 // 日志记录器

public:
    CommunicationSystemLX(GroupManagerLX* grpManager, ServiceManagerLX* srvManager);

    // 系统初始化
    void initialize();

    // 系统运行主逻辑
    void run();

    // 系统退出
    void shutdown();

    // 主菜单
    void displayMenu() const;
};
