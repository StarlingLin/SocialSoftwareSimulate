#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager) {
}

void UIManagerLX::start()
{
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
}

void UIManagerLX::displayMainMenu()
{
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
    PasswdLX passwdManager;
    cout << "请输入您想要注册的用户名：";
    string username;
    cin >> username;
    cout << "请输入您的密码：";
    string password;
    cin >> password;

    if (!passwdManager.userExists(username))
    {
        userManager->addUser(username, username, "2000-01-01", "1", "默认位置");
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
    cout << "请选择要进入的服务：" << endl;
    cout << "1. QQ服务" << endl;
    cout << "2. 微信服务" << endl;
    cout << "3. 微A服务" << endl;
    cout << "4. 微B服务" << endl;
    cout << "5. 返回主菜单" << endl;
    int choice;
    cin >> choice;

    string username = "当前登录用户名"; // 假设存储了登录用户信息
    string nickname;
    switch (choice)
    {
    case 1:
        cout << "进入QQ服务。" << endl;
        pageStack.push("Service Menu");
        break;
    case 2:
        if (!serviceManager->isServiceEnabled(username, "WeChat"))
        {
            cout << "未开通微信服务，请输入昵称以注册：";
            cin >> nickname;
            serviceManager->registerService(username, "WeChat", true, nickname);
            logger->log("用户开通了微信服务。");
            cout << "微信服务开通成功！" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 3:
        if (!serviceManager->isServiceEnabled(username, "MicroA"))
        {
            cout << "未开通微A服务，将直接使用QQ ID注册。" << endl;
            serviceManager->registerService(username, "MicroA", false, "");
            logger->log("用户开通了微A服务。");
            cout << "微A服务开通成功！" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 4:
        if (!serviceManager->isServiceEnabled(username, "MicroB"))
        {
            cout << "未开通微B服务，请输入昵称以注册：";
            cin >> nickname;
            serviceManager->registerService(username, "MicroB", true, nickname);
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
    cout << "欢迎进入服务菜单！" << endl;
    cout << "1. 查看个人信息" << endl;
    cout << "2. 查看好友列表" << endl;
    cout << "3. 查看群组信息" << endl;
    cout << "4. 返回服务选择" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // 调用具体服务的个人信息显示逻辑
        logger->log("用户查看了个人信息。");
        break;
    case 2:
        // 调用具体服务的好友列表显示逻辑
        logger->log("用户查看了好友列表。");
        break;
    case 3:
        // 调用具体服务的群组信息显示逻辑
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
