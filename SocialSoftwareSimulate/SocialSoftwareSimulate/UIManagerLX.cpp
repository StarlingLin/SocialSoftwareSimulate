#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager), database(database), currentService(""), loggedInUser("") {
}

void UIManagerLX::start()
{
    // 加载服务数据
    database->loadServices(serviceManager);
    database->loadGroups(groupManager);
    database->loadUsers(*userManager);

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

        // 保存用户信息到本地文件
        database->saveUsers(*userManager);

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
    cout << "2. 用户管理" << endl;
    cout << "3. 群组管理" << endl;
    cout << "4. 返回服务选择" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
		pageStack.push("User Info");
        displayUserInfo();
        break;
    case 2:
        pageStack.push("User Management");
        displayUserManagementMenu();
        break;
    case 3:
        pageStack.push("Group Management");
        displayGroupManagementMenu();
        break;
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}

void UIManagerLX::displayUserInfo()
{
    system("cls");
    cout << "用户个人信息：" << endl;
    UserLX* user = userManager->getUser(loggedInUser);
    if (user)
    {
        cout << "用户ID: " << user->getQQID() << endl;
        cout << "昵称: " << user->getNickname() << endl;
        cout << "出生时间: " << user->getBirthDate() << endl;
        cout << "号码申请时间: " << user->getTAge() << endl;
        cout << "所在地: " << user->getLocation() << endl;
    }
    else
    {
        cout << "未找到用户信息。" << endl;
    }

    cout << "\n1. 返回" << endl;
    cout << "2. 修改信息" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        pageStack.pop();
        break;
    case 2:
        modifyUserInfo();
        break;
    default:
        cout << "无效选项，请重试。" << endl;
        break;
    }
}

void UIManagerLX::modifyUserInfo()
{
    system("cls");
    cout << "修改用户信息：" << endl;
    cout << "请输入新的昵称：";
    string newNickname;
    cin >> newNickname;
    cout << "请输入新的所在地：";
    string newLocation;
    cin >> newLocation;
	cout << "请输入新的出生时间：";
	string newBirthDate;
	cin >> newBirthDate;
    UserLX* user = userManager->getUser(loggedInUser);
	cout << "请输入新的号码申请时间：";
	string newTAge;
	cin >> newTAge;
    if (user)
    {
        user->setNickname(newNickname);
        user->setLocation(newLocation);
		user->setBirthDate(newBirthDate);
		user->setTAge(newTAge);
        cout << "信息修改成功！" << endl;
        logger->log("用户修改了个人信息。");
		database->saveUsers(*userManager);
    }
    else
    {
        cout << "未找到用户信息。" << endl;
    }

	system("pause");
	pageStack.pop();
}

void UIManagerLX::displayUserManagementMenu()
{
    system("cls");
    cout << "用户管理菜单" << endl;
    cout << "1. 添加好友" << endl;
    cout << "2. 删除好友" << endl;
    cout << "3. 查看好友列表" << endl;
    cout << "4. 返回" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "请输入好友ID: ";
        string friendID;
        cin >> friendID;
        friendManager.addFriend(currentService, loggedInUser, friendID);
        cout << "好友添加成功！" << endl;
        break;
    }
    case 2:
    {
        cout << "请输入要删除的好友ID: ";
        string friendID;
        cin >> friendID;
        friendManager.removeFriend(currentService, loggedInUser, friendID);
        cout << "好友删除成功！" << endl;
        break;
    }
    case 3:
    {
        cout << "好友列表：" << endl;
        auto friends = friendManager.getFriends(currentService, loggedInUser);
        for (const auto& friendID : friends)
        {
            cout << friendID << endl;
        }
        break;
    }
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}

void UIManagerLX::displayGroupManagementMenu()
{
    system("cls");
    cout << "群组管理菜单" << endl;
    cout << "1. 查看群组" << endl;
    cout << "2. 加入群组" << endl;
    cout << "3. 退出群组" << endl;
    cout << "4. 返回" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "您已加入的群组：" << endl;
        if (groupManager)
        {
            auto groups = groupManager->getGroups(loggedInUser);
            for (const auto& groupID : groups)
            {
                cout << "群组ID: " << groupID << endl;
            }
        }
        else
        {
            cout << "无法获取群组信息！" << endl;
        }
        break;
    }
    case 2:
    {
        cout << "请输入要加入的群组ID: ";
        int groupID;
        cin >> groupID;
        if (groupManager)
        {
            groupManager->joinGroup(groupID, loggedInUser);
            cout << "加入群组成功！" << endl;
        }
        else
        {
            cout << "无法加入群组！" << endl;
        }
        break;
    }
    case 3:
    {
        cout << "请输入要退出的群组ID: ";
        int groupID;
        cin >> groupID;
        if (groupManager)
        {
            groupManager->leaveGroup(groupID, loggedInUser);
            cout << "退出群组成功！" << endl;
        }
        else
        {
            cout << "无法退出群组！" << endl;
        }
        break;
    }
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "无效选项，请重新选择。" << endl;
        break;
    }
}
