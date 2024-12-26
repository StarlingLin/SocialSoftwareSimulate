#pragma once

#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

class UserLX
{
private:
    string qqID;                       // ͳһID
    string nickname;                   // �û��ǳ�
    string birthDate;                  // ����ʱ��
    string tAge;                       // ��������ʱ��
    string location;                   // ���ڵ�
    map<int, string> serviceIDs;       // ��������ID�б�
    vector<string> friendList;         // �����б�
    vector<string> groupList;          // Ⱥ���б�
    vector<string> boundServices;      // �Ѱ󶨵ķ�������

public:
    // Ĭ�Ϲ��캯��
    UserLX();

    // ���캯��
    UserLX(const string& id, const string& name, const string& birth,
        const string& age, const string& loc);

    // ��ӷ���ID
    void addServiceID(int serviceNumber, const string& id);

    // ��ѯ����ID
    string getServiceID(int serviceNumber) const;

    // ����Ƿ�󶨵�����
    bool isBoundToService(const string& serviceName) const;

    // ��ȡ���з���ID������Ϣ
    map<int, string> getAllServiceIDs() const;

    // �Ƴ�����ID
    void removeServiceID(int serviceNumber);

    // �󶨷����û�
    void bindToService(const string& serviceName);

    // ��ȡ�û��󶨵����з���
    vector<string> getAllBoundServices() const;

    // ���ѹ���
    void addFriend(const string& friendID);
    void removeFriend(const string& friendID);
    vector<string> getFriendList() const;

    // Ⱥ�����
    void joinGroup(const string& groupID);
    void leaveGroup(const string& groupID);
    vector<string> getGroupList() const;

    // ��ʾ�û�������Ϣ
    void displayUserInfo() const;

    // ������Ϣ����
    string getQQID() const;            // ��ȡͳһID
    string getNickname() const;        // ��ȡ�ǳ�
    void setNickname(const string& name);
    string getBirthDate() const;       // ��ȡ����ʱ��
    void setBirthDate(const string& birth);
    string getTAge() const;            // ��ȡ��������ʱ��
    void setTAge(const string& age);
    string getLocation() const;        // ��ȡ���ڵ�
    void setLocation(const string& loc);
};
