#include "FriendLX.h"
#include <algorithm>

// ��Ӻ���
void FriendLX::addFriend(const string& serviceName, const string& userID, const string& friendID)
{
    if (find(serviceFriendMap[serviceName][userID].begin(), serviceFriendMap[serviceName][userID].end(), friendID) == serviceFriendMap[serviceName][userID].end())
    {
        serviceFriendMap[serviceName][userID].push_back(friendID);
        serviceFriendMap[serviceName][friendID].push_back(userID); // ˫�����
    }
}

// ɾ������
void FriendLX::removeFriend(const string& serviceName, const string& userID, const string& friendID)
{
    auto& userFriends = serviceFriendMap[serviceName][userID];
    userFriends.erase(remove(userFriends.begin(), userFriends.end(), friendID), userFriends.end());

    auto& friendFriends = serviceFriendMap[serviceName][friendID];
    friendFriends.erase(remove(friendFriends.begin(), friendFriends.end(), userID), friendFriends.end());
}

// ��ȡ�����б�
vector<string> FriendLX::getFriends(const string& serviceName, const string& userID) const
{
    auto serviceIt = serviceFriendMap.find(serviceName);
    if (serviceIt != serviceFriendMap.end())
    {
        auto userIt = serviceIt->second.find(userID);
        if (userIt != serviceIt->second.end())
        {
            return userIt->second;
        }
    }
    return {};
}
