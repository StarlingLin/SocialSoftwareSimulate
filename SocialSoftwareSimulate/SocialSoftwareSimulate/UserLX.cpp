#include "UserLX.h"
#include <iostream>
#include <algorithm>
using namespace std;

// Ĭ�Ϲ��캯��
UserLX::UserLX()
    : qqID(""), nickname(""), birthDate(""), tAge(""), location("") {
}

// ���캯��
UserLX::UserLX(const string& id, const string& name, const string& birth,
    const string& age, const string& loc)
    : qqID(id), nickname(name), birthDate(birth), tAge(age), location(loc) {
}

// ��ӷ���ID
void UserLX::addServiceID(int serviceNumber, const string& id)
{
    if (serviceIDs.find(serviceNumber) != serviceIDs.end())
    {
        cout << "����ID " << serviceNumber << " �Ѱ�ʵ����ʵIDΪ��" << serviceIDs[serviceNumber] << endl;
        return;
    }
    serviceIDs[serviceNumber] = id;
    cout << "����ID " << serviceNumber << " ��ʵ�ɹ�����ʵIDΪ��" << id << endl;
}

// ��ѯ����ID
string UserLX::getServiceID(int serviceNumber) const
{
    auto it = serviceIDs.find(serviceNumber);
    if (it != serviceIDs.end())
    {
        return it->second;
    }
    return qqID; // ����ͳһID��ΪĬ��ֵ
}

// ����Ƿ��ʵ������
bool UserLX::isBoundToService(int serviceNumber) const
{
    return serviceIDs.find(serviceNumber) != serviceIDs.end();
}

// ��ȡ���з���ID����ʵ��Ϣ
map<int, string> UserLX::getAllServiceIDs() const
{
    return serviceIDs;
}

// �Ƴ�����ID
void UserLX::removeServiceID(int serviceNumber)
{
    if (serviceIDs.erase(serviceNumber) > 0)
    {
        cout << "����ID " << serviceNumber << " �ѳɹ����" << endl;
    }
    else
    {
        cout << "����ID " << serviceNumber << " δ��ʵ��" << endl;
    }
}

// ��ʵ�����û�
void UserLX::bindToService(const string& serviceName)
{
    if (find(boundServices.begin(), boundServices.end(), serviceName) == boundServices.end())
    {
        boundServices.push_back(serviceName);
    }
}

// ��ȡ�û���ʵ�����з���
vector<string> UserLX::getAllBoundServices() const
{
    return boundServices;
}

// ���ѹ���
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

// Ⱥ�����
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

// ��ʾ�û�������Ϣ
void UserLX::displayUserInfo() const
{
    cout << "�û���Ϣ��" << endl;
    cout << "QQ ID: " << qqID << endl;
    cout << "�ǳ�: " << nickname << endl;
    cout << "����ʱ��: " << birthDate << endl;
    cout << "��������ʱ��: " << tAge << endl;
    cout << "���ڵ�: " << location << endl;

    cout << "�����б�" << endl;
    for (const auto& friendID : friendList)
    {
        cout << "����ID: " << friendID << endl;
    }

    cout << "Ⱥ���б�" << endl;
    for (const auto& groupID : groupList)
    {
        cout << "Ⱥ��ID: " << groupID << endl;
    }

    cout << "��ʵ�ķ���" << endl;
    for (const auto& service : serviceIDs)
    {
        cout << "����ID: " << service.first << ", ��ʵID: " << service.second << endl;
    }

    cout << "�Ѱ�ʵ�ķ������ƣ�" << endl;
    for (const auto& service : boundServices)
    {
        cout << "��������: " << service << endl;
    }
}

// ������Ϣ������
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