#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// 基础服务类
class ServiceLX
{
protected:
    string serviceName;                                // 服务名称
    bool usesSharedID;                                // 是否使用公用ID (qqID)
    map<string, bool> userLoginStatus;                // 用户ID -> 登录状态
    map<string, vector<string>> userFriends;          // 用户ID -> 好友列表
    map<int, vector<string>> userGroups;              // 群组ID -> 群成员
    map<string, string> userNicknames;                // 用户ID -> 昵称

public:
    ServiceLX(const string& name, bool sharedID);

    // 用户登录管理
    virtual void loginUser(const string& userID);
    virtual void logoutUser(const string& userID);
    virtual bool isUserLoggedIn(const string& userID) const;

    // 检查用户是否绑定服务
    virtual bool isUserBound(const string& userID) const;

    // 好友管理
    virtual void addFriend(const string& userID, const string& friendID);
    virtual void removeFriend(const string& userID, const string& friendID);
    virtual vector<string> getFriends(const string& userID) const;

    // 群组管理
    virtual void joinGroup(const string& userID, int groupID);
    virtual void leaveGroup(const string& userID, int groupID);
    virtual vector<int> getGroups(const string& userID) const;

    // 服务信息
    string getServiceName() const;
    virtual void displayServiceInfo() const;

    // 获取所有已登录用户
    vector<string> getLoggedUsers() const;

    // 注册用户
    virtual void registerUser(const string& userID, const string& serviceID, const string& nickname);

    // 获取所有绑定用户
    virtual vector<string> getAllBoundUsers() const;

    // 获取用户昵称
    virtual string getNickname(const string& userID) const;

    // 检查服务是否启用
    bool isActive() const;

    virtual ~ServiceLX() = default;
};

// QQ服务类
class QQServiceLX : public ServiceLX
{
private:
    map<int, vector<string>> groupAdmins; // 群组管理员

public:
    QQServiceLX();

    // 群组管理员管理
    void addAdmin(int groupID, const string& userID);
    void removeAdmin(int groupID, const string& userID);
    vector<string> getAdmins(int groupID) const;

    void displayServiceInfo() const override;

    // 用户注册
    void registerUser(const string& userID, const string& serviceID, const string& nickname) override;

    // 检查用户绑定
    bool isUserBound(const string& userID) const override;

    // 获取所有绑定用户
    vector<string> getAllBoundUsers() const override;

    // 获取用户昵称
    string getNickname(const string& userID) const override;
};

// WX服务类
class WXServiceLX : public ServiceLX
{
public:
    WXServiceLX();

    // 提供推荐好友
    vector<string> getRecommendedFriends(const string& userID, const ServiceLX& qqService) const;

    void displayServiceInfo() const override;

    // 用户注册
    void registerUser(const string& userID, const string& serviceID, const string& nickname) override;

    // 检查用户绑定
    bool isUserBound(const string& userID) const override;

    // 获取所有绑定用户
    vector<string> getAllBoundUsers() const override;

    // 获取用户昵称
    string getNickname(const string& userID) const override;
};
