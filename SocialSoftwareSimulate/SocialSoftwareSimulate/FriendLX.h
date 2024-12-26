#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

class FriendLX
{
private:
    map<string, map<string, vector<string>>> serviceFriendMap; // ������ -> �û�ID -> ����ID�б�

public:
    // ��Ӻ���
    void addFriend(const string& serviceName, const string& userID, const string& friendID);

    // ɾ������
    void removeFriend(const string& serviceName, const string& userID, const string& friendID);

    // ��ȡ�����б�
    vector<string> getFriends(const string& serviceName, const string& userID) const;
};