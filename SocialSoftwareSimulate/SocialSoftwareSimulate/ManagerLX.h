#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>
#include "ServiceLX.h"
#include "UserLX.h"

using namespace std;

// �û�������
class UserManagerLX {
private:
    map<string, UserLX> users; // �û�ID -> �û�ʵ��

public:
    // ����û�
    void addUser(const string& userID, const string& nickname, const string& birthDate, const string& tAge, const string& location);

    // �Ƴ��û�
    void removeUser(const string& userID);

    // ��ȡ�û�ʵ��
    UserLX* getUser(const string& userID);

    // ����û��Ƿ����
    bool userExists(const string& userID) const;

    // չʾ�����û���Ϣ
    void displayAllUsers() const;

    // ��ȡ�����û�
    map<string, UserLX> getAllUsers() const;
};

// ���ࣺȺ�Ĺ�����
class GroupManagerLX {
protected:
    map<int, vector<string>> groups; // Ⱥ��ID -> Ⱥ��Ա�б�

public:
    virtual ~GroupManagerLX() = default;

    // ����Ⱥ��
    virtual void createGroup(int groupID);

    // ɾ��Ⱥ��
    virtual void removeGroup(int groupID);

    // ����Ⱥ��
    virtual void joinGroup(int groupID, const string& userID);

    // �˳�Ⱥ��
    virtual void leaveGroup(int groupID, const string& userID);

    // ��ȡȺ��Ա
    virtual vector<string> getGroupMembers(int groupID) const;

    // չʾ����Ⱥ��
    virtual void displayAllGroups() const;

    // ��ȡ����Ⱥ��
    map<int, vector<string>> getAllGroups() const;
};

// �����ࣺQQȺ�Ĺ�����
class QQGroupManagerLX : public GroupManagerLX {
private:
    map<int, vector<string>> groupAdmins; // Ⱥ��ID -> ����Ա�б�

public:
    // ��ӹ���Ա
    void addAdmin(int groupID, const string& userID);

    // �Ƴ�����Ա
    void removeAdmin(int groupID, const string& userID);

    // ��ȡ����Ա
    vector<string> getAdmins(int groupID) const;

    // չʾ����Ⱥ��
    void displayAllGroups() const override;
};

// �����ࣺ΢��Ⱥ�Ĺ�����
class WXGroupManagerLX : public GroupManagerLX {
public:
    // չʾ����Ⱥ��
    void displayAllGroups() const override;
};

// ���ࣺ���������
class ServiceManagerLX {
protected:
    map<string, ServiceLX*> services; // �������� -> ����ʵ��

public:
    virtual ~ServiceManagerLX() = default;

    // ��ӷ���
    virtual void addService(const string& serviceName, ServiceLX* service);

    // �Ƴ�����
    virtual void removeService(const string& serviceName);

    // ��ȡ����
    virtual ServiceLX* getService(const string& serviceName) const;

    // չʾ���з�����Ϣ
    virtual void displayAllServices() const;

    // ��ȡ���з���
    map<string, ServiceLX*> getAllServices() const;
};

// �����ࣺQQ���������
class QQServiceManagerLX : public ServiceManagerLX {
public:
    void displayAllServices() const override;
};

// �����ࣺ΢�ŷ��������
class WXServiceManagerLX : public ServiceManagerLX {
public:
    void displayAllServices() const override;
};
