#include "UserMenuLX.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// 显示登录页面
void UserMenuLX::showLoginPage()
{
    string serviceName;
    string userID;
    string password;

    cout << "\n--- 用户登录 ---\n";
    cout << "请输入服务名称（如 QQ 或 微信）：";
    cin >> serviceName;
    cout << "请输入用户ID：";
    cin >> userID;
    cout << "请输入密码：";
    cin >> password;

    if (validateLogin(serviceName, userID, password))
    {
        cout << "登录成功！\n";
        currentService = serviceName; // 设置当前服务
        currentUserID = userID;       // 设置当前用户ID

        // 加载服务相关数据
        loadServiceData(serviceName, userID);

        navigateTo(0);                // 导航到服务主页面
        showServiceMainPage();
    }
    else
    {
        cout << "登录失败，请重试。\n";
        showLoginPage();
    }
}

// 用户注册页面
void UserMenuLX::showRegisterPage()
{
    string serviceName;
    string userID;
    string password;
    string nickname;
    string birthDate;
    string location;
    string registrationDate;

    cout << "\n--- 用户注册 ---\n";
    cout << "请输入服务名称（如 QQ 或 微信）：";
    cin >> serviceName;
    cout << "请输入用户ID：";
    cin >> userID;

    // 检查用户是否已存在
    if (authInfo[serviceName].find(userID) != authInfo[serviceName].end())
    {
        cout << "用户已存在，请直接登录。\n";
        showLoginPage();
        return;
    }

    cout << "请输入密码：";
    cin >> password;
    cout << "请输入昵称：";
    cin >> nickname;
    cout << "请输入出生日期（格式 YYYY-MM-DD）：";
    cin >> birthDate;
    cout << "请输入所在地：";
    cin >> location;

    // 获取当前日期作为注册日期
    registrationDate = "2024-12-26"; // 假设当前日期

    // 保存用户认证信息
    saveAuthInfo(serviceName, userID, password);

    // 保存用户到 users.txt
    ofstream usersFile("users.txt", ios::app);
    if (usersFile.is_open())
    {
        usersFile << currentUserID << " "    // QQ ID (统一ID)
            << serviceName << " "      // 服务ID
            << userID << " "          // 用户在服务的ID
            << nickname << " "        // 昵称
            << birthDate << " "       // 出生日期
            << registrationDate << " " // 号码申请时间
            << location << endl;       // 所在地
        usersFile.close();
        cout << "用户信息已保存到 users.txt。\n";
    }
    else
    {
        cerr << "无法打开 users.txt 进行保存。\n";
    }

    cout << "注册成功！请登录。\n";
    showLoginPage();
}

// 验证登录信息
bool UserMenuLX::validateLogin(const string& serviceName, const string& userID, const string& password)
{
    auto serviceIt = authInfo.find(serviceName);
    if (serviceIt != authInfo.end())
    {
        auto userIt = serviceIt->second.find(userID);
        if (userIt != serviceIt->second.end() && userIt->second == password)
        {
            return true;
        }
    }
    return false;
}

// 保存用户认证信息到文件
void UserMenuLX::saveAllAuthInfo()
{
    ofstream outFile("passwd.txt");
    if (!outFile.is_open())
    {
        cerr << "无法打开文件 passwd.txt 进行写入。\n";
        return;
    }

    for (const auto& service : authInfo)
    {
        for (const auto& user : service.second)
        {
            outFile << service.first << " " << user.first << " " << user.second << endl;
        }
    }

    outFile.close();
    cout << "用户认证信息已保存。\n";
}

// 保存用户认证信息
void UserMenuLX::saveAuthInfo(const string& serviceName, const string& userID, const string& password)
{
    authInfo[serviceName][userID] = password;

    saveAllAuthInfo(); // 保存全部认证信息到文件
}

// 加载用户认证信息
void UserMenuLX::loadAuthInfo()
{
    ifstream inFile("passwd.txt");
    if (!inFile.is_open())
    {
        cerr << "无法打开文件 passwd.txt 进行读取。\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string serviceName, userID, password;
        ss >> serviceName >> userID >> password;
        authInfo[serviceName][userID] = password;
    }

    inFile.close();
}

// 加载服务相关数据
void UserMenuLX::loadServiceData(const string& serviceName, const string& userID)
{
    cout << "加载 " << serviceName << " 服务的好友和群组数据...\n";

    string friendsFile = serviceName + "_friends.txt";
    string groupsFile = serviceName + "_groups.txt";

    ifstream friendsStream(friendsFile);
    ifstream groupsStream(groupsFile);

    friendData[serviceName].clear();
    groupData[serviceName].clear();

    if (friendsStream.is_open())
    {
        string friendID;
        while (getline(friendsStream, friendID))
        {
            friendData[serviceName].push_back(friendID);
        }
        friendsStream.close();
        cout << "好友数据加载成功！\n";
    }
    else
    {
        cout << "好友数据文件未找到，默认加载为空。\n";
    }

    if (groupsStream.is_open())
    {
        string groupID;
        while (getline(groupsStream, groupID))
        {
            groupData[serviceName].push_back(groupID);
        }
        groupsStream.close();
        cout << "群组数据加载成功！\n";
    }
    else
    {
        cout << "群组数据文件未找到，默认加载为空。\n";
    }
}

// 保存服务相关数据
void UserMenuLX::saveServiceData(const string& serviceName)
{
    cout << "保存 " << serviceName << " 服务的数据...\n";

    string friendsFile = serviceName + "_friends.txt";
    string groupsFile = serviceName + "_groups.txt";

    ofstream friendsStream(friendsFile);
    if (friendsStream.is_open())
    {
        for (const string& friendID : friendData[serviceName])
        {
            friendsStream << friendID << endl;
        }
        friendsStream.close();
        cout << "好友数据保存成功！\n";
    }
    else
    {
        cerr << "无法打开好友数据文件进行写入。\n";
    }

    ofstream groupsStream(groupsFile);
    if (groupsStream.is_open())
    {
        for (const string& groupID : groupData[serviceName])
        {
            groupsStream << groupID << endl;
        }
        groupsStream.close();
        cout << "群组数据保存成功！\n";
    }
    else
    {
        cerr << "无法打开群组数据文件进行写入。\n";
    }
}

// 显示服务主页面
void UserMenuLX::showServiceMainPage()
{
    int choice = -1;
    pageStack.push(0); // 服务主页面编号为 0

    while (!pageStack.empty())
    {
        int currentPage = pageStack.top();

        switch (currentPage)
        {
        case 0: // 服务主页面
            cout << "\n--- " << currentService << " 主页面 ---\n";
            cout << "1. 好友管理\n";
            cout << "2. 群组管理\n";
            cout << "3. 修改个人信息\n";
            cout << "4. 注销账户\n";
            cout << "5. 退出服务\n";
            choice = getUserInput();

            if (choice == 1) navigateTo(1);
            else if (choice == 2) navigateTo(2);
            else if (choice == 3) navigateTo(3);
            else if (choice == 4) navigateTo(4);
            else if (choice == 5) goBack();
            break;

        case 1: // 好友管理页面
            showFriendMenu();
            break;

        case 2: // 群组管理页面
            showGroupMenu();
            break;

        case 3: // 修改个人信息页面
            showEditProfilePage();
            break;

        case 4: // 注销账户页面
            showDeleteAccountPage();
            break;
        }
    }
}

// 好友管理页面
void UserMenuLX::showFriendMenu()
{
    cout << "\n--- " << currentService << " 好友管理 ---\n";
    cout << "当前好友列表:\n";

    if (friendData[currentService].empty())
    {
        cout << "暂无好友。\n";
    }
    else
    {
        for (const string& friendID : friendData[currentService])
        {
            cout << "好友: " << friendID << "\n";
        }
    }

    cout << "\n1. 返回上一页\n";
    int choice = getUserInput();
    if (choice == 1)
    {
        goBack();
    }
}

// 群组管理页面
void UserMenuLX::showGroupMenu()
{
    cout << "\n--- " << currentService << " 群组管理 ---\n";
    cout << "当前群组列表:\n";

    if (groupData[currentService].empty())
    {
        cout << "暂无群组。\n";
    }
    else
    {
        for (const string& groupID : groupData[currentService])
        {
            cout << "群组: " << groupID << "\n";
        }
    }

    cout << "\n1. 返回上一页\n";
    int choice = getUserInput();
    if (choice == 1)
    {
        goBack();
    }
}

// 修改个人信息页面
void UserMenuLX::showEditProfilePage()
{
    string newNickname, newPassword, newLocation;

    cout << "\n--- 修改个人信息 ---\n";
    cout << "请输入新的昵称：";
    cin >> newNickname;
    cout << "请输入新的密码：";
    cin >> newPassword;
    cout << "请输入新的所在地：";
    cin >> newLocation;

    // 更新用户密码信息
    authInfo[currentService][currentUserID] = newPassword;

    // 更新并保存用户信息到 users.txt
    vector<string> updatedUsers;
    ifstream usersFile("users.txt");
    string line;

    while (getline(usersFile, line))
    {
        stringstream ss(line);
        string qqID, serviceName, userID, nickname, birthDate, tAge, location;
        ss >> qqID >> serviceName >> userID >> nickname >> birthDate >> tAge >> location;

        if (serviceName == currentService && userID == currentUserID)
        {
            updatedUsers.push_back(qqID + " " + serviceName + " " + userID + " " + newNickname + " " + birthDate + " " + tAge + " " + newLocation);
        }
        else
        {
            updatedUsers.push_back(line);
        }
    }
    usersFile.close();

    ofstream outFile("users.txt", ios::trunc);
    for (const string& updatedLine : updatedUsers)
    {
        outFile << updatedLine << endl;
    }
    outFile.close();

    // 保存到密码文件
    saveAllAuthInfo();

    cout << "个人信息修改成功！\n";
    goBack();
}

// 注销账户页面
void UserMenuLX::showDeleteAccountPage()
{
    string confirmation;

    cout << "\n--- 注销账户 ---\n";
    cout << "确认注销当前账户？（yes/no）：";
    cin >> confirmation;

    if (confirmation == "yes")
    {
        // 从内存中删除用户数据
        authInfo[currentService].erase(currentUserID);

        // 更新 users.txt 文件
        vector<string> updatedUsers;
        ifstream usersFile("users.txt");
        string line;

        while (getline(usersFile, line))
        {
            stringstream ss(line);
            string qqID, serviceName, userID, nickname, birthDate, tAge, location;
            ss >> qqID >> serviceName >> userID >> nickname >> birthDate >> tAge >> location;

            if (!(serviceName == currentService && userID == currentUserID))
            {
                updatedUsers.push_back(line);
            }
        }
        usersFile.close();

        ofstream outFile("users.txt", ios::trunc);
        for (const string& updatedLine : updatedUsers)
        {
            outFile << updatedLine << endl;
        }
        outFile.close();

        // 保存到密码文件
        saveAllAuthInfo();

        cout << "账户已注销。\n";
        goBack();
    }
    else
    {
        cout << "取消注销操作。\n";
        goBack();
    }
}

// 辅助函数：处理用户输入
int UserMenuLX::getUserInput()
{
    int choice;
    cout << "请输入选项：";
    cin >> choice;
    return choice;
}

// 导航到指定页面
void UserMenuLX::navigateTo(int pageID)
{
    system("cls");
    pageStack.push(pageID);
}

// 返回上一级页面
void UserMenuLX::goBack()
{
    system("cls");
    if (!pageStack.empty())
    {
        pageStack.pop();
    }

    if (pageStack.empty())
    {
        saveServiceData(currentService);
        cout << "\n已退出用户系统。\n";
        exit(0);
    }
}
