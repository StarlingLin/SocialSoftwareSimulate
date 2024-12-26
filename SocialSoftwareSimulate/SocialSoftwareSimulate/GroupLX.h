#pragma once

#include <string>
#include <vector>
#include <map>

using namespace std;

// 基类：通用群组
class BaseGroupLX
{
protected:
    map<string, map<int, vector<string>>> serviceGroupMembers; // 服务名 -> 群ID -> 群成员ID列表
    map<string, map<int, string>> serviceGroupOwners;          // 服务名 -> 群ID -> 群主ID

public:
    virtual ~BaseGroupLX() = default;

    // 创建群（设置群主）
    virtual void createGroup(const string& serviceName, int groupID, const string& ownerID) = 0;

    // 加入群
    virtual void joinGroup(const string& serviceName, int groupID, const string& userID);

    // 退出群
    virtual void leaveGroup(const string& serviceName, int groupID, const string& userID);

    // 查询群成员
    virtual vector<string> getGroupMembers(const string& serviceName, int groupID) const;

    // 检查是否为群主
    virtual bool isOwner(const string& serviceName, int groupID, const string& userID) const;
};

// 派生类：仅群主管理的群
class OwnerOnlyGroupLX : public BaseGroupLX
{
public:
    void createGroup(const string& serviceName, int groupID, const string& ownerID) override;

    // 检查权限（只有群主有权限）
    bool hasPermission(const string& serviceName, int groupID, const string& userID) const;
};

// 派生类：群主和管理员管理的群
class OwnerAndAdminGroupLX : public BaseGroupLX
{
private:
    map<string, map<int, vector<string>>> serviceGroupAdmins; // 服务名 -> 群ID -> 管理员ID列表

public:
    void createGroup(const string& serviceName, int groupID, const string& ownerID) override;

    // 添加管理员
    void addAdmin(const string& serviceName, int groupID, const string& userID);

    // 移除管理员
    void removeAdmin(const string& serviceName, int groupID, const string& userID);

    // 检查权限（群主和管理员有权限）
    bool hasPermission(const string& serviceName, int groupID, const string& userID) const;
};
