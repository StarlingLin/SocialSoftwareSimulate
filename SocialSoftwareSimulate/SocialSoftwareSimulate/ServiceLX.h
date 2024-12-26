#pragma once

#include <string>
#include <map>
#include <vector>
#include <iostream>

using namespace std;

// ����������
class ServiceLX
{
protected:
    string serviceName;                                // ��������
    bool usesSharedID;                                // �Ƿ�ʹ�ù���ID (qqID)
    map<string, bool> userLoginStatus;                // �û�ID -> ��¼״̬
    map<string, vector<string>> userFriends;          // �û�ID -> �����б�
    map<int, vector<string>> userGroups;              // Ⱥ��ID -> Ⱥ��Ա
    map<string, string> userNicknames;                // �û�ID -> �ǳ�

public:
    ServiceLX(const string& name, bool sharedID);

    // �û���¼����
    virtual void loginUser(const string& userID);
    virtual void logoutUser(const string& userID);
    virtual bool isUserLoggedIn(const string& userID) const;

    // ����û��Ƿ�󶨷���
    virtual bool isUserBound(const string& userID) const;

    // ���ѹ���
    virtual void addFriend(const string& userID, const string& friendID);
    virtual void removeFriend(const string& userID, const string& friendID);
    virtual vector<string> getFriends(const string& userID) const;

    // Ⱥ�����
    virtual void joinGroup(const string& userID, int groupID);
    virtual void leaveGroup(const string& userID, int groupID);
    virtual vector<int> getGroups(const string& userID) const;

    // ������Ϣ
    string getServiceName() const;
    virtual void displayServiceInfo() const;

    // ��ȡ�����ѵ�¼�û�
    vector<string> getLoggedUsers() const;

    // ע���û�
    virtual void registerUser(const string& userID, const string& serviceID, const string& nickname);

    // ��ȡ���а��û�
    virtual vector<string> getAllBoundUsers() const;

    // ��ȡ�û��ǳ�
    virtual string getNickname(const string& userID) const;

    // �������Ƿ�����
    bool isActive() const;

    virtual ~ServiceLX() = default;
};

// QQ������
class QQServiceLX : public ServiceLX
{
private:
    map<int, vector<string>> groupAdmins; // Ⱥ�����Ա

public:
    QQServiceLX();

    // Ⱥ�����Ա����
    void addAdmin(int groupID, const string& userID);
    void removeAdmin(int groupID, const string& userID);
    vector<string> getAdmins(int groupID) const;

    void displayServiceInfo() const override;

    // �û�ע��
    void registerUser(const string& userID, const string& serviceID, const string& nickname) override;

    // ����û���
    bool isUserBound(const string& userID) const override;

    // ��ȡ���а��û�
    vector<string> getAllBoundUsers() const override;

    // ��ȡ�û��ǳ�
    string getNickname(const string& userID) const override;
};

// WX������
class WXServiceLX : public ServiceLX
{
public:
    WXServiceLX();

    // �ṩ�Ƽ�����
    vector<string> getRecommendedFriends(const string& userID, const ServiceLX& qqService) const;

    void displayServiceInfo() const override;

    // �û�ע��
    void registerUser(const string& userID, const string& serviceID, const string& nickname) override;

    // ����û���
    bool isUserBound(const string& userID) const override;

    // ��ȡ���а��û�
    vector<string> getAllBoundUsers() const override;

    // ��ȡ�û��ǳ�
    string getNickname(const string& userID) const override;
};
