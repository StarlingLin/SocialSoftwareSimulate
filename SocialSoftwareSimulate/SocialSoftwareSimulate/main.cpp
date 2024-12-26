#include "ManagerLX.h"
#include "UIManagerLX.h"
#include "LoggerLX.h"
#include "ServiceLX.h"

int main() {
    // 初始化日志管理器
    LoggerLX logger;

    // 初始化用户管理器
    UserManagerLX userManager;

    // 初始化服务管理器
    ServiceManagerLX serviceManager;

    // 初始化群组管理器
    GroupManagerLX groupManager;

    // 初始化数据库管理器
    DatabaseLX database;

    // 添加服务
    serviceManager.addService("QQ", new QQServiceLX());         // QQ 服务
    serviceManager.addService("WeChat", new WXServiceLX());     // 微信服务
    serviceManager.addService("MicroA", new QQServiceLX());     // 微A服务（使用QQ服务逻辑）
    serviceManager.addService("MicroB", new WXServiceLX());     // 微B服务（使用微信服务逻辑）

    // 初始化 UI 管理器
    UIManagerLX uiManager(&logger, &userManager, &serviceManager, &groupManager, &database);


    // 启动系统
    uiManager.start();

    return 0;
}
