#include "ManagerLX.h"
#include <algorithm>
#include <iostream>

using namespace std;

// UserManagerLX
void UserManagerLX::addUser(const string& userID, const string& nickname, const string& birthDate, const string& tAge, const string& location)
{
    UserLX newUser(userID, nickname, birthDate, tAge, location);
    users[userID] = newUser;
    cout << "�û� " << userID << " ����ӡ�" << endl;
}

void UserManagerLX::removeUser(const string& userID)
{
    if (users.erase(userID))
    {
        cout << "�û� " << userID << " ���Ƴ���" << endl;
    }
    else
    {
        cout << "�û� " << userID << " δ�ҵ���" << endl;
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
    cout << "�����û���" << endl;
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
        cout << "�û� " << userID << " �Ѱ󶨷��� " << serviceName << "��" << endl;
    }
    else
    {
        cout << "�û� " << userID << " δ�ҵ����޷��󶨷���" << endl;
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
    cout << "Ⱥ�� " << groupID << " �Ѵ�����" << endl;
}

void GroupManagerLX::removeGroup(int groupID)
{
    if (groups.erase(groupID))
    {
        cout << "Ⱥ�� " << groupID << " ���Ƴ���" << endl;
    }
    else
    {
        cout << "Ⱥ�� " << groupID << " δ�ҵ���" << endl;
    }
}

void GroupManagerLX::joinGroup(int groupID, const string& userID)
{
    groups[groupID].push_back(userID);
    cout << "�û� " << userID << " ������Ⱥ�� " << groupID << "��" << endl;
}

void GroupManagerLX::leaveGroup(int groupID, const string& userID)
{
    auto& members = groups[groupID];
    members.erase(remove(members.begin(), members.end(), userID), members.end());
    cout << "�û� " << userID << " �˳���Ⱥ�� " << groupID << "��" << endl;
}

vector<string> GroupManagerLX::getGroupMembers(int groupID) const
{
    auto it = groups.find(groupID);
    return it != groups.end() ? it->second : vector<string>{};
}

void GroupManagerLX::displayAllGroups() const
{
    cout << "����Ⱥ�飺" << endl;
    for (const auto& group : groups)
    {
        cout << "Ⱥ��ID: " << group.first << ", ��Ա: ";
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
    cout << "�û� " << userID << " �����ΪȺ�� " << groupID << " �Ĺ���Ա��" << endl;
}

void QQGroupManagerLX::removeAdmin(int groupID, const string& userID)
{
    auto& admins = groupAdmins[groupID];
    admins.erase(remove(admins.begin(), admins.end(), userID), admins.end());
    cout << "�û� " << userID << " �Ѵ�Ⱥ�� " << groupID << " �Ĺ���Ա���Ƴ���" << endl;
}

vector<string> QQGroupManagerLX::getAdmins(int groupID) const
{
    auto it = groupAdmins.find(groupID);
    return it != groupAdmins.end() ? it->second : vector<string>{};
}

void QQGroupManagerLX::displayAllGroups() const
{
    GroupManagerLX::displayAllGroups();
    cout << "����Ա���飺" << endl;
    for (const auto& group : groupAdmins)
    {
        cout << "Ⱥ��ID: " << group.first << ", ����Ա: ";
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
    cout << "΢��Ⱥ���޹���Աϵͳ��" << endl;
}

// ServiceManagerLX
void ServiceManagerLX::addService(const string& serviceName, ServiceLX* service)
{
    services[serviceName] = service;
    cout << "���� " << serviceName << " ����ӡ�" << endl;
}

void ServiceManagerLX::removeService(const string& serviceName)
{
    if (services.erase(serviceName))
    {
        cout << "���� " << serviceName << " ���Ƴ���" << endl;
    }
    else
    {
        cout << "���� " << serviceName << " δ�ҵ���" << endl;
    }
}

ServiceLX* ServiceManagerLX::getService(const string& serviceName) const
{
    auto it = services.find(serviceName);
    return it != services.end() ? it->second : nullptr;
}

void ServiceManagerLX::displayAllServices() const
{
    cout << "���з���" << endl;
    for (const auto& service : services)
    {
        cout << "��������: " << service.first << endl;
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
        cout << "���� " << serviceName << " δ�ҵ����޷�ע�ᡣ" << endl;
        return;
    }

    if (bindToQQID)
    {
        it->second->registerUser(userID, serviceName, nickname);
        cout << "�û� " << userID << " ͨ����QQ ID ע���˷��� " << serviceName << "���ǳ�Ϊ " << nickname << "��" << endl;
    }
    else
    {
        it->second->registerUser(userID, serviceName, nickname);
        cout << "�û� " << userID << " ʹ����IDע���˷��� " << serviceName << "���ǳ�Ϊ " << nickname << "��" << endl;
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
        it->second->updateUserNickname(userID, newNickname); // ʹ�� ServiceLX �ṩ�Ľӿ�
    }
}


// QQServiceManagerLX
void QQServiceManagerLX::displayAllServices() const
{
    ServiceManagerLX::displayAllServices();
    cout << "�ض���QQ����" << endl;
}

// WXServiceManagerLX
void WXServiceManagerLX::displayAllServices() const
{
    ServiceManagerLX::displayAllServices();
    cout << "�ض���΢�ŷ���" << endl;
}
