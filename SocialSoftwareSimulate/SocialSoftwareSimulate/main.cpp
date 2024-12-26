#include <iostream>
#include "AdminMenuLX.h"
#include "UserMenuLX.h"
#include "FileLX.h"

using namespace std;

int main()
{
    // 初始化用户菜单和文件处理模块
    UserMenuLX userMenu;
    FileLX fileHandler;

    // 加载用户认证信息
    userMenu.loadAuthInfo();

    // 加载其他服务数据
    auto userData = fileHandler.loadCompleteUserData("users.txt");
    auto groupData = fileHandler.loadGroupData("groups.txt");
    auto friendData = fileHandler.loadFriendData("friends.txt");
    auto serviceData = fileHandler.loadServiceData("services.txt");

    cout << "数据加载成功！\n";

    // 主菜单选择
    int choice;
    cout << "请选择模式：\n";
    cout << "1. 后台管理页面\n";
    cout << "2. 用户登录页面\n";
    cout << "3. 用户注册页面\n";
    cin >> choice;

    system("cls");

    if (choice == 1)
    {
        AdminMenuLX adminMenu;
        adminMenu.showMainMenu();
    }
    else if (choice == 2)
    {
        userMenu.showLoginPage();
    }
    else if (choice == 3)
    {
        userMenu.showRegisterPage();
    }
    else
    {
        cout << "无效选择，程序退出。\n";
    }

    // 保存数据
    fileHandler.saveCompleteUserData("users.txt", userData);
    fileHandler.saveGroupData("groups.txt", groupData);
    fileHandler.saveFriendData("friends.txt", friendData);
    fileHandler.saveServiceData("services.txt", serviceData);

    cout << "数据保存成功！\n";

    return 0;
}
