#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

class FriendLX
{
private:
    map<string, map<string, vector<string>>> serviceFriendMap; // 服务名 -> 用户ID -> 好友ID列表

public:
    // 添加好友
    void addFriend(const string& serviceName, const string& userID, const string& friendID);

    // 删除好友
    void removeFriend(const string& serviceName, const string& userID, const string& friendID);

    // 获取好友列表
    vector<string> getFriends(const string& serviceName, const string& userID) const;
};