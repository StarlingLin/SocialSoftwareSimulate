#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class UserLX
{
private:
    string qqID;                       // 统一ID
    string nickname;                   // 用户昵称
    string birthDate;                  // 出生时间
    string tAge;                       // 号码申请时间
    string location;                   // 所在地
    map<int, string> serviceIDs;       // 独立服务ID列表
    vector<string> friendList;         // 好友列表
    vector<string> groupList;          // 群组列表
    vector<string> boundServices;      // 已绑定的服务名称

public:
    // 默认构造函数
    UserLX();

    // 构造函数
    UserLX(const string& id, const string& name, const string& birth,
        const string& age, const string& loc);

    // 添加服务ID
    void addServiceID(int serviceNumber, const string& id);

    // 查询服务ID
    string getServiceID(int serviceNumber) const;

    // 检查是否绑定到服务
    bool isBoundToService(const string& serviceName) const;

    // 获取所有服务ID及绑定信息
    map<int, string> getAllServiceIDs() const;

    // 移除服务ID
    void removeServiceID(int serviceNumber);

    // 绑定服务到用户
    void bindToService(const string& serviceName);

    // 获取用户绑定的所有服务
    vector<string> getAllBoundServices() const;

    // 好友管理
    void addFriend(const string& friendID);
    void removeFriend(const string& friendID);
    vector<string> getFriendList() const;

    // 群组管理
    void joinGroup(const string& groupID);
    void leaveGroup(const string& groupID);
    vector<string> getGroupList() const;

    // 显示用户完整信息
    void displayUserInfo() const;

    // 基本信息管理
    string getQQID() const;            // 获取统一ID
    string getNickname() const;        // 获取昵称
    void setNickname(const string& name);
    string getBirthDate() const;       // 获取出生时间
    void setBirthDate(const string& birth);
    string getTAge() const;            // 获取号码申请时间
    void setTAge(const string& age);
    string getLocation() const;        // 获取所在地
    void setLocation(const string& loc);
};
