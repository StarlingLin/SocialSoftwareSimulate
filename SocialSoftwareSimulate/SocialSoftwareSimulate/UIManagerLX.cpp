#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager), database(database), currentService(""), loggedInUser("") {
}

void UIManagerLX::start()
{
    // 加载服务数据
    database->loadServices(serviceManager);

    pageStack.push("Main Menu");
    while (!pageStack.empty())
    {
        string currentPage = pageStack.top();
        if (currentPage == "Main Menu")
        {
            displayMainMenu();
        }
        else if (currentPage == "Login Menu")
        {
            displayLoginMenu();
        }
        else if (currentPage == "Register Menu")
        {
            displayRegisterMenu();
        }
        else if (currentPage == "Service Selection")
        {
            displayServiceSelectionMenu();
        }
        else if (currentPage == "Service Menu")
        {
            displayServiceMenu();
        }
        else if (currentPage == "User Management")
        {
            displayUserManagementMenu();
        }
        else if (currentPage == "Group Management")
        {
            displayGroupManagementMenu();
        }
    }

    // 退出前保存服务数据
    database->saveServices(serviceManager);
}

void UIManagerLX::displayMainMenu()
{
    system("cls");
    cout << "欢迎来到社交模拟软件！" << endl;
    cout << "1. 登录" << endl;
    cout << "2. 注册" << endl;
    cout << "3. 退出" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        pageStack.push("Login Menu");
        logger->log("用户选择登录。");
        break;
    case 2:
        pageStack.push("Register Menu");
        logger->log("用户选择注册。");
        break;
    case 3:
        pageStack.pop();
        logger->log("用户退出程序。");
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}

void UIManagerLX::displayLoginMenu()
{
    system("cls");
    PasswdLX passwdManager;
    cout << "请输入您的用户名：";
    string username;
    cin >> username;
    cout << "请输入您的密码：";
    string password;
    cin >> password;

    if (passwdManager.validatePassword(username, password))
    {
        logger->log("用户 " + username + " 成功登录。");
        cout << "登录成功！" << endl;
        loggedInUser = username;
        pageStack.pop();
        pageStack.push("Service Selection");
    }
    else
    {
        logger->log("用户 " + username + " 登录失败。");
        cout << "用户名或密码错误，请重试。" << endl;
    }
}

void UIManagerLX::displayRegisterMenu()
{
    system("cls");
    PasswdLX passwdManager;
    cout << "请输入您想要注册的用户名：";
    string username;
    cin >> username;
    cout << "请输入您的密码：";
    string password;
    cin >> password;
    cout << "请输入您的昵称：";
    string nickname;
    cin >> nickname;

    if (!passwdManager.userExists(username))
    {
        userManager->addUser(username, nickname, "2000-01-01", "1", "默认位置");
        passwdManager.setPassword(username, password);
        logger->log("用户 " + username + " 注册成功。");
        cout << "注册成功！" << endl;
        pageStack.pop();
    }
    else
    {
        logger->log("用户 " + username + " 注册失败，用户名已存在。");
        cout << "用户名已存在，请重试。" << endl;
    }
}

void UIManagerLX::displayServiceSelectionMenu()
{
    system("cls");
    cout << "请选择要进入的服务：" << endl;
    cout << "1. QQ服务" << endl;
    cout << "2. 微信服务" << endl;
    cout << "3. 微A服务" << endl;
    cout << "4. 微B服务" << endl;
    cout << "5. 返回主菜单" << endl;
    int choice;
    cin >> choice;

    string nickname;
    string id;
    switch (choice)
    {
    case 1:
        currentService = "QQ";
        pageStack.push("Service Menu");
        break;
    case 2:
        currentService = "WeChat";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "未开通微信服务，请输入服务ID：";
            cin >> id;
            cout << "请输入昵称：";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, true, nickname);

            database->saveServices(serviceManager);

            logger->log("用户开通了微信服务。");
            cout << "微信服务开通成功！" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 3:
        currentService = "MicroA";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "未开通微A服务，请输入昵称：";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, false, nickname);

            database->saveServices(serviceManager);

            logger->log("用户开通了微A服务。");
            cout << "微A服务开通成功！" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 4:
        currentService = "MicroB";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "未开通微B服务，请输入服务ID：";
            cin >> id;
            cout << "请输入昵称：";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, true, nickname);

            database->saveServices(serviceManager);

            logger->log("用户开通了微B服务。");
            cout << "微B服务开通成功！" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 5:
        pageStack.pop();
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}

void UIManagerLX::displayServiceMenu()
{
    system("cls");
    cout << "欢迎进入 " << currentService << " 服务菜单！" << endl;
    cout << "1. 查看个人信息" << endl;
    cout << "2. 查看好友列表" << endl;
    cout << "3. 查看群组信息" << endl;
    cout << "4. 返回服务选择" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "个人信息：" << endl;
        cout << "昵称: " << serviceManager->getService(currentService)->getNickname(loggedInUser) << endl;
        logger->log("用户查看了个人信息。");
        break;
    case 2:
        cout << "好友列表：" << endl;
        for (const string& friendID : serviceManager->getService(currentService)->getFriends(loggedInUser))
        {
            cout << friendID << endl;
        }
        logger->log("用户查看了好友列表。");
        break;
    case 3:
        cout << "群组信息：" << endl;
        for (int groupID : serviceManager->getService(currentService)->getGroups(loggedInUser))
        {
            cout << "群组ID: " << groupID << endl;
        }
        logger->log("用户查看了群组信息。");
        break;
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}

void UIManagerLX::displayUserManagementMenu()
{
    system("cls");
    cout << "\n===== 用户管理菜单 =====" << endl;
    cout << "1. 添加用户" << endl;
    cout << "2. 移除用户" << endl;
    cout << "3. 显示所有用户" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << "=======================" << endl;
    cout << "请输入选项: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // 调用添加用户逻辑
        break;
    case 2:
        // 调用移除用户逻辑
        break;
    case 3:
        // 调用显示所有用户逻辑
        break;
    case 0:
        return;
    default:
        cout << "无效选项，请重试。" << endl;
        break;
    }
}

void UIManagerLX::displayGroupManagementMenu()
{
    system("cls");
    cout << "\n===== 群组管理菜单 =====" << endl;
    cout << "1. 创建群组" << endl;
    cout << "2. 解散群组" << endl;
    cout << "3. 显示所有群组" << endl;
    cout << "0. 返回主菜单" << endl;
    cout << "=======================" << endl;
    cout << "请输入选项: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // 调用创建群组逻辑
        break;
    case 2:
        // 调用解散群组逻辑
        break;
    case 3:
        // 调用显示所有群组逻辑
        break;
    case 0:
        return;
    default:
        cout << "无效选项，请重试。" << endl;
        break;
    }
}
