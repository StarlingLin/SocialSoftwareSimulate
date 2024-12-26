#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

// ���ࣺͨ��Ⱥ��
class BaseGroupLX
{
protected:
    map<string, map<int, vector<string>>> serviceGroupMembers; // ������ -> ȺID -> Ⱥ��ԱID�б�
    map<string, map<int, string>> serviceGroupOwners;          // ������ -> ȺID -> Ⱥ��ID

public:
    virtual ~BaseGroupLX() = default;

    // ����Ⱥ������Ⱥ����
    virtual void createGroup(const string& serviceName, int groupID, const string& ownerID) = 0;

    // ����Ⱥ
    virtual void joinGroup(const string& serviceName, int groupID, const string& userID);

    // �˳�Ⱥ
    virtual void leaveGroup(const string& serviceName, int groupID, const string& userID);

    // ��ѯȺ��Ա
    virtual vector<string> getGroupMembers(const string& serviceName, int groupID) const;

    // ����Ƿ�ΪȺ��
    virtual bool isOwner(const string& serviceName, int groupID, const string& userID) const;
};

// �����ࣺ��Ⱥ�������Ⱥ
class OwnerOnlyGroupLX : public BaseGroupLX
{
public:
    void createGroup(const string& serviceName, int groupID, const string& ownerID) override;

    // ���Ȩ�ޣ�ֻ��Ⱥ����Ȩ�ޣ�
    bool hasPermission(const string& serviceName, int groupID, const string& userID) const;
};

// �����ࣺȺ���͹���Ա�����Ⱥ
class OwnerAndAdminGroupLX : public BaseGroupLX
{
private:
    map<string, map<int, vector<string>>> serviceGroupAdmins; // ������ -> ȺID -> ����ԱID�б�

public:
    void createGroup(const string& serviceName, int groupID, const string& ownerID) override;

    // ��ӹ���Ա
    void addAdmin(const string& serviceName, int groupID, const string& userID);

    // �Ƴ�����Ա
    void removeAdmin(const string& serviceName, int groupID, const string& userID);

    // ���Ȩ�ޣ�Ⱥ���͹���Ա��Ȩ�ޣ�
    bool hasPermission(const string& serviceName, int groupID, const string& userID) const;
};
