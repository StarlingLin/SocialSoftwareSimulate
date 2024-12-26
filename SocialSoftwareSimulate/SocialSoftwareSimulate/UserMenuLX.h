#pragma once

#include <stack>
#include <string>
#include <map>
#include <vector>

using namespace std;

class UserMenuLX
{
private:
    stack<int> pageStack; // 页面栈，用于管理菜单导航
    string currentService; // 当前登录的服务名称
    string currentUserID; // 当前登录的用户ID
    map<string, map<string, string>> authInfo; // 服务名 -> 用户ID -> 密码
    map<string, vector<string>> friendData; // 服务名 -> 好友列表
    map<string, vector<string>> groupData;  // 服务名 -> 群组列表

public:
    // 显示登录页面
    void showLoginPage();

    // 用户注册页面
    void showRegisterPage();

    // 验证登录信息
    bool validateLogin(const string& serviceName, const string& userID, const string& password);

    // 保存用户认证信息到文件
    void saveAllAuthInfo();

    // 保存用户认证信息
    void saveAuthInfo(const string& serviceName, const string& userID, const string& password);

    // 加载用户认证信息
    void loadAuthInfo();

    // 加载服务相关数据
    void loadServiceData(const string& serviceName, const string& userID);

    // 保存服务相关数据
    void saveServiceData(const string& serviceName);

    // 显示服务主页面
    void showServiceMainPage();

    // 好友管理页面
    void showFriendMenu();

    // 群组管理页面
    void showGroupMenu();

    // 修改个人信息页面
    void showEditProfilePage();

    // 注销账户页面
    void showDeleteAccountPage();

    // 导航到指定页面
    void navigateTo(int pageID);

    // 返回上一级页面
    void goBack();

    // 辅助函数：处理用户输入
    int getUserInput();
};
