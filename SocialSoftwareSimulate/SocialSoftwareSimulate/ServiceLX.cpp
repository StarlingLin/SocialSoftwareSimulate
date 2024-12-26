#include "ServiceLX.h"
#include <iostream>
#include <algorithm>

using namespace std;

// ServiceLX构造函数
ServiceLX::ServiceLX(const string& name, bool sharedID)
    : serviceName(name), usesSharedID(sharedID) {
}

void ServiceLX::loginUser(const string& userID) {
    userLoginStatus[userID] = true;
    cout << userID << " 登录成功。" << endl;
}

void ServiceLX::logoutUser(const string& userID) {
    userLoginStatus[userID] = false;
    cout << userID << " 已退出。" << endl;
}

bool ServiceLX::isUserLoggedIn(const string& userID) const {
    auto it = userLoginStatus.find(userID);
    return it != userLoginStatus.end() && it->second;
}

bool ServiceLX::isUserBound(const string& userID) const {
    return userLoginStatus.find(userID) != userLoginStatus.end();
}

void ServiceLX::addFriend(const string& userID, const string& friendID) {
    if (find(userFriends[userID].begin(), userFriends[userID].end(), friendID) == userFriends[userID].end()) {
        userFriends[userID].push_back(friendID);
        userFriends[friendID].push_back(userID); // 双向添加
    }
}

void ServiceLX::removeFriend(const string& userID, const string& friendID) {
    auto& friends = userFriends[userID];
    friends.erase(remove(friends.begin(), friends.end(), friendID), friends.end());

    auto& friendList = userFriends[friendID];
    friendList.erase(remove(friendList.begin(), friendList.end(), userID), friendList.end());
}

vector<string> ServiceLX::getFriends(const string& userID) const {
    auto it = userFriends.find(userID);
    if (it != userFriends.end()) {
        return it->second;
    }
    return {};
}

void ServiceLX::joinGroup(const string& userID, int groupID) {
    if (find(userGroups[groupID].begin(), userGroups[groupID].end(), userID) == userGroups[groupID].end()) {
        userGroups[groupID].push_back(userID);
    }
}

void ServiceLX::leaveGroup(const string& userID, int groupID) {
    auto& groupMembers = userGroups[groupID];
    groupMembers.erase(remove(groupMembers.begin(), groupMembers.end(), userID), groupMembers.end());
}

vector<int> ServiceLX::getGroups(const string& userID) const {
    vector<int> groups;
    for (map<int, vector<string>>::const_iterator it = userGroups.begin(); it != userGroups.end(); ++it) {
        int groupID = it->first;
        const vector<string>& members = it->second;
        if (find(members.begin(), members.end(), userID) != members.end()) {
            groups.push_back(groupID);
        }
    }
    return groups;
}

string ServiceLX::getServiceName() const {
    return serviceName;
}

void ServiceLX::displayServiceInfo() const {
    cout << "Service Name: " << serviceName << endl;
    cout << "Uses Shared ID: " << (usesSharedID ? "Yes" : "No") << endl;
}

vector<string> ServiceLX::getLoggedUsers() const {
    vector<string> loggedUsers;
    for (map<string, bool>::const_iterator it = userLoginStatus.begin(); it != userLoginStatus.end(); ++it) {
        if (it->second) {
            loggedUsers.push_back(it->first);
        }
    }
    return loggedUsers;
}

bool ServiceLX::isActive() const {
    return !userLoginStatus.empty();
}

// QQServiceLX构造函数
QQServiceLX::QQServiceLX()
    : ServiceLX("QQ", true) {
}

void QQServiceLX::addAdmin(int groupID, const string& userID) {
    if (find(groupAdmins[groupID].begin(), groupAdmins[groupID].end(), userID) == groupAdmins[groupID].end()) {
        groupAdmins[groupID].push_back(userID);
    }
}

void QQServiceLX::removeAdmin(int groupID, const string& userID) {
    auto& admins = groupAdmins[groupID];
    admins.erase(remove(admins.begin(), admins.end(), userID), admins.end());
}

vector<string> QQServiceLX::getAdmins(int groupID) const {
    auto it = groupAdmins.find(groupID);
    if (it != groupAdmins.end()) {
        return it->second;
    }
    return {};
}

void QQServiceLX::displayServiceInfo() const {
    cout << "QQ Service: " << endl;
    ServiceLX::displayServiceInfo();
    cout << "Supports Admins: Yes" << endl;
}

// WXServiceLX构造函数
WXServiceLX::WXServiceLX()
    : ServiceLX("WeChat", false) {
}

vector<string> WXServiceLX::getRecommendedFriends(const string& userID, const ServiceLX& qqService) const {
    return qqService.getFriends(userID); // 推荐好友来源于 QQ 服务
}

void WXServiceLX::displayServiceInfo() const {
    cout << "WeChat Service: " << endl;
    ServiceLX::displayServiceInfo();
    cout << "Supports Admins: No" << endl;
}
