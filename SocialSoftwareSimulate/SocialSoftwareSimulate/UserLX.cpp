#include "UserLX.h"
#include <iostream>
#include <algorithm>
using namespace std;

// 默认构造函数
UserLX::UserLX()
    : qqID(""), nickname(""), birthDate(""), tAge(""), location("") {
}

// 构造函数
UserLX::UserLX(const string& id, const string& name, const string& birth,
    const string& age, const string& loc)
    : qqID(id), nickname(name), birthDate(birth), tAge(age), location(loc) {
}

// 添加服务ID
void UserLX::addServiceID(int serviceNumber, const string& id)
{
    if (serviceIDs.find(serviceNumber) != serviceIDs.end())
    {
        cout << "服务ID " << serviceNumber << " 已绑定，绑定ID为：" << serviceIDs[serviceNumber] << endl;
        return;
    }
    serviceIDs[serviceNumber] = id;
    cout << "服务ID " << serviceNumber << " 绑定成功，绑定ID为：" << id << endl;
}

// 查询服务ID
string UserLX::getServiceID(int serviceNumber) const
{
    auto it = serviceIDs.find(serviceNumber);
    if (it != serviceIDs.end())
    {
        return it->second;
    }
    return qqID; // 返回统一ID作为默认值
}

// 检查是否绑定到服务
bool UserLX::isBoundToService(const string& serviceName) const
{
    return find(boundServices.begin(), boundServices.end(), serviceName) != boundServices.end();
}

// 获取所有服务ID及绑定信息
map<int, string> UserLX::getAllServiceIDs() const
{
    return serviceIDs;
}

// 移除服务ID
void UserLX::removeServiceID(int serviceNumber)
{
    if (serviceIDs.erase(serviceNumber) > 0)
    {
        cout << "服务ID " << serviceNumber << " 已成功解绑。" << endl;
    }
    else
    {
        cout << "服务ID " << serviceNumber << " 未绑定。" << endl;
    }
}

// 绑定服务到用户
void UserLX::bindToService(const string& serviceName)
{
    if (find(boundServices.begin(), boundServices.end(), serviceName) == boundServices.end())
    {
        boundServices.push_back(serviceName);
    }
}

// 获取用户绑定的所有服务
vector<string> UserLX::getAllBoundServices() const
{
    return boundServices;
}

// 好友管理
void UserLX::addFriend(const string& friendID)
{
    if (find(friendList.begin(), friendList.end(), friendID) == friendList.end())
    {
        friendList.push_back(friendID);
    }
}

void UserLX::removeFriend(const string& friendID)
{
    friendList.erase(remove(friendList.begin(), friendList.end(), friendID), friendList.end());
}

vector<string> UserLX::getFriendList() const
{
    return friendList;
}

// 群组管理
void UserLX::joinGroup(const string& groupID)
{
    if (find(groupList.begin(), groupList.end(), groupID) == groupList.end())
    {
        groupList.push_back(groupID);
    }
}

void UserLX::leaveGroup(const string& groupID)
{
    groupList.erase(remove(groupList.begin(), groupList.end(), groupID), groupList.end());
}

vector<string> UserLX::getGroupList() const
{
    return groupList;
}

// 显示用户完整信息
void UserLX::displayUserInfo() const
{
    cout << "用户信息：" << endl;
    cout << "QQ ID: " << qqID << endl;
    cout << "昵称: " << nickname << endl;
    cout << "出生时间: " << birthDate << endl;
    cout << "号码申请时间: " << tAge << endl;
    cout << "所在地: " << location << endl;

    cout << "好友列表：" << endl;
    for (const auto& friendID : friendList)
    {
        cout << "好友ID: " << friendID << endl;
    }

    cout << "群组列表：" << endl;
    for (const auto& groupID : groupList)
    {
        cout << "群组ID: " << groupID << endl;
    }

    cout << "绑定的服务：" << endl;
    for (const auto& service : serviceIDs)
    {
        cout << "服务ID: " << service.first << ", 绑定ID: " << service.second << endl;
    }

    cout << "已绑定的服务名称：" << endl;
    for (const auto& service : boundServices)
    {
        cout << "服务名称: " << service << endl;
    }
}

// 基本信息管理方法
string UserLX::getQQID() const
{
    return qqID;
}

string UserLX::getNickname() const
{
    return nickname;
}

void UserLX::setNickname(const string& name)
{
    nickname = name;
}

string UserLX::getBirthDate() const
{
    return birthDate;
}

void UserLX::setBirthDate(const string& birth)
{
    birthDate = birth;
}

string UserLX::getTAge() const
{
    return tAge;
}

void UserLX::setTAge(const string& age)
{
    tAge = age;
}

string UserLX::getLocation() const
{
    return location;
}

void UserLX::setLocation(const string& loc)
{
    location = loc;
}
