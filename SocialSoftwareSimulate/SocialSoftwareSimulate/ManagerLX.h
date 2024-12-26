#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "ServiceLX.h"
#include "UserLX.h"

using namespace std;

// 用户管理类
class UserManagerLX {
private:
    map<string, UserLX> users; // 用户ID -> 用户实例

public:
    // 添加用户
    void addUser(const string& userID, const string& nickname, const string& birthDate, const string& tAge, const string& location);

    // 移除用户
    void removeUser(const string& userID);

    // 获取用户实例
    UserLX* getUser(const string& userID);

    // 检查用户是否存在
    bool userExists(const string& userID) const;

    // 展示所有用户信息
    void displayAllUsers() const;

    // 获取所有用户
    map<string, UserLX> getAllUsers() const;
};

// 基类：群聊管理类
class GroupManagerLX {
protected:
    map<int, vector<string>> groups; // 群组ID -> 群成员列表

public:
    virtual ~GroupManagerLX() = default;

    // 创建群组
    virtual void createGroup(int groupID);

    // 删除群组
    virtual void removeGroup(int groupID);

    // 加入群组
    virtual void joinGroup(int groupID, const string& userID);

    // 退出群组
    virtual void leaveGroup(int groupID, const string& userID);

    // 获取群成员
    virtual vector<string> getGroupMembers(int groupID) const;

    // 展示所有群组
    virtual void displayAllGroups() const;

    // 获取所有群组
    map<int, vector<string>> getAllGroups() const;
};

// 派生类：QQ群聊管理类
class QQGroupManagerLX : public GroupManagerLX {
private:
    map<int, vector<string>> groupAdmins; // 群组ID -> 管理员列表

public:
    // 添加管理员
    void addAdmin(int groupID, const string& userID);

    // 移除管理员
    void removeAdmin(int groupID, const string& userID);

    // 获取管理员
    vector<string> getAdmins(int groupID) const;

    // 展示所有群组
    void displayAllGroups() const override;
};

// 派生类：微信群聊管理类
class WXGroupManagerLX : public GroupManagerLX {
public:
    // 展示所有群组
    void displayAllGroups() const override;
};

// 基类：服务管理类
class ServiceManagerLX {
protected:
    map<string, ServiceLX*> services; // 服务名称 -> 服务实例

public:
    virtual ~ServiceManagerLX() = default;

    // 添加服务
    virtual void addService(const string& serviceName, ServiceLX* service);

    // 移除服务
    virtual void removeService(const string& serviceName);

    // 获取服务
    virtual ServiceLX* getService(const string& serviceName) const;

    // 展示所有服务信息
    virtual void displayAllServices() const;

    // 获取所有服务
    map<string, ServiceLX*> getAllServices() const;
};

// 派生类：QQ服务管理类
class QQServiceManagerLX : public ServiceManagerLX {
public:
    void displayAllServices() const override;
};

// 派生类：微信服务管理类
class WXServiceManagerLX : public ServiceManagerLX {
public:
    void displayAllServices() const override;
};
