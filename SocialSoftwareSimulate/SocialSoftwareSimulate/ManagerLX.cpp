#include "ManagerLX.h"
#include <algorithm>
#include <iostream>

using namespace std;

// UserManagerLX
void UserManagerLX::addUser(const string& userID, const string& nickname, const string& birthDate, const string& tAge, const string& location)
{
    UserLX newUser(userID, nickname, birthDate, tAge, location);
    users[userID] = newUser;
    cout << "用户 " << userID << " 已添加。" << endl;
}

void UserManagerLX::removeUser(const string& userID)
{
    if (users.erase(userID))
    {
        cout << "用户 " << userID << " 已移除。" << endl;
    }
    else
    {
        cout << "用户 " << userID << " 未找到。" << endl;
    }
}

UserLX* UserManagerLX::getUser(const string& userID)
{
    auto it = users.find(userID);
    return it != users.end() ? &it->second : nullptr;
}

bool UserManagerLX::userExists(const string& userID) const
{
    return users.find(userID) != users.end();
}

void UserManagerLX::displayAllUsers() const
{
    cout << "所有用户：" << endl;
    for (const auto& userPair : users)
    {
        const UserLX& user = userPair.second;
        user.displayUserInfo();
    }
}

map<string, UserLX> UserManagerLX::getAllUsers() const
{
    return users;
}

void UserManagerLX::bindService(const string& userID, const string& serviceName)
{
    auto it = users.find(userID);
    if (it != users.end())
    {
        it->second.bindToService(serviceName);
        cout << "用户 " << userID << " 已绑定服务 " << serviceName << "。" << endl;
    }
    else
    {
        cout << "用户 " << userID << " 未找到，无法绑定服务。" << endl;
    }
}

bool UserManagerLX::isServiceBound(const string& userID, const string& serviceName) const
{
    auto it = users.find(userID);
    if (it != users.end())
    {
        return it->second.isBoundToService(serviceName);
    }
    return false;
}

// GroupManagerLX
void GroupManagerLX::createGroup(int groupID)
{
    groups[groupID] = {};
    cout << "群组 " << groupID << " 已创建。" << endl;
}

void GroupManagerLX::removeGroup(int groupID)
{
    if (groups.erase(groupID))
    {
        cout << "群组 " << groupID << " 已移除。" << endl;
    }
    else
    {
        cout << "群组 " << groupID << " 未找到。" << endl;
    }
}

void GroupManagerLX::joinGroup(int groupID, const string& userID)
{
    groups[groupID].push_back(userID);
    cout << "用户 " << userID << " 加入了群组 " << groupID << "。" << endl;
}

void GroupManagerLX::leaveGroup(int groupID, const string& userID)
{
    auto& members = groups[groupID];
    members.erase(remove(members.begin(), members.end(), userID), members.end());
    cout << "用户 " << userID << " 退出了群组 " << groupID << "。" << endl;
}

vector<string> GroupManagerLX::getGroupMembers(int groupID) const
{
    auto it = groups.find(groupID);
    return it != groups.end() ? it->second : vector<string>{};
}

void GroupManagerLX::displayAllGroups() const
{
    cout << "所有群组：" << endl;
    for (const auto& group : groups)
    {
        cout << "群组ID: " << group.first << ", 成员: ";
        for (const auto& member : group.second)
        {
            cout << member << " ";
        }
        cout << endl;
    }
}

map<int, vector<string>> GroupManagerLX::getAllGroups() const
{
    return groups;
}

vector<int> GroupManagerLX::getGroups(const string& userID) const
{
    vector<int> userGroups;
    for (const auto& group : groups)
    {
        if (find(group.second.begin(), group.second.end(), userID) != group.second.end())
        {
            userGroups.push_back(group.first);
        }
    }
    return userGroups;
}

// QQGroupManagerLX
void QQGroupManagerLX::addAdmin(int groupID, const string& userID)
{
    groupAdmins[groupID].push_back(userID);
    cout << "用户 " << userID << " 已添加为群组 " << groupID << " 的管理员。" << endl;
}

void QQGroupManagerLX::removeAdmin(int groupID, const string& userID)
{
    auto& admins = groupAdmins[groupID];
    admins.erase(remove(admins.begin(), admins.end(), userID), admins.end());
    cout << "用户 " << userID << " 已从群组 " << groupID << " 的管理员中移除。" << endl;
}

vector<string> QQGroupManagerLX::getAdmins(int groupID) const
{
    auto it = groupAdmins.find(groupID);
    return it != groupAdmins.end() ? it->second : vector<string>{};
}

void QQGroupManagerLX::displayAllGroups() const
{
    GroupManagerLX::displayAllGroups();
    cout << "管理员详情：" << endl;
    for (const auto& group : groupAdmins)
    {
        cout << "群组ID: " << group.first << ", 管理员: ";
        for (const auto& admin : group.second)
        {
            cout << admin << " ";
        }
        cout << endl;
    }
}

// WXGroupManagerLX
void WXGroupManagerLX::displayAllGroups() const
{
    GroupManagerLX::displayAllGroups();
    cout << "微信群组无管理员系统。" << endl;
}

// ServiceManagerLX
void ServiceManagerLX::addService(const string& serviceName, ServiceLX* service)
{
    services[serviceName] = service;
    cout << "服务 " << serviceName << " 已添加。" << endl;
}

void ServiceManagerLX::removeService(const string& serviceName)
{
    if (services.erase(serviceName))
    {
        cout << "服务 " << serviceName << " 已移除。" << endl;
    }
    else
    {
        cout << "服务 " << serviceName << " 未找到。" << endl;
    }
}

ServiceLX* ServiceManagerLX::getService(const string& serviceName) const
{
    auto it = services.find(serviceName);
    return it != services.end() ? it->second : nullptr;
}

void ServiceManagerLX::displayAllServices() const
{
    cout << "所有服务：" << endl;
    for (const auto& service : services)
    {
        cout << "服务名称: " << service.first << endl;
    }
}

map<string, ServiceLX*> ServiceManagerLX::getAllServices() const
{
    return services;
}

void ServiceManagerLX::registerService(const string& userID, const string& serviceName, bool bindToQQID, const string& nickname)
{
    auto it = services.find(serviceName);
    if (it == services.end())
    {
        cout << "服务 " << serviceName << " 未找到，无法注册。" << endl;
        return;
    }

    if (bindToQQID)
    {
        it->second->registerUser(userID, serviceName, nickname);
        cout << "用户 " << userID << " 通过绑定QQ ID 注册了服务 " << serviceName << "，昵称为 " << nickname << "。" << endl;
    }
    else
    {
        it->second->registerUser(userID, serviceName, nickname);
        cout << "用户 " << userID << " 使用新ID注册了服务 " << serviceName << "，昵称为 " << nickname << "。" << endl;
    }
}

bool ServiceManagerLX::isServiceEnabled(const string& userID, const string& serviceName) const
{
    auto service = services.find(serviceName);
    if (service != services.end())
    {
        return service->second->isUserBound(userID);
    }
    return false;
}

string ServiceManagerLX::getNickname(const string& serviceName, const string& userID) const
{
    auto it = services.find(serviceName);
    if (it != services.end() && it->second)
    {
        return it->second->getUserNickname(userID);
    }
    return "";
}

void ServiceManagerLX::updateNickname(const string& serviceName, const string& userID, const string& newNickname)
{
    auto it = services.find(serviceName);
    if (it != services.end() && it->second)
    {
        it->second->updateUserNickname(userID, newNickname); // 使用 ServiceLX 提供的接口
    }
}


// QQServiceManagerLX
void QQServiceManagerLX::displayAllServices() const
{
    ServiceManagerLX::displayAllServices();
    cout << "特定于QQ服务。" << endl;
}

// WXServiceManagerLX
void WXServiceManagerLX::displayAllServices() const
{
    ServiceManagerLX::displayAllServices();
    cout << "特定于微信服务。" << endl;
}
