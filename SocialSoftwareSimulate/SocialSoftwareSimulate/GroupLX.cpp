#include "GroupLX.h"
#include <algorithm>

// BaseGroupLX
void BaseGroupLX::joinGroup(const string& serviceName, int groupID, const string& userID)
{
    if (find(serviceGroupMembers[serviceName][groupID].begin(), serviceGroupMembers[serviceName][groupID].end(), userID) == serviceGroupMembers[serviceName][groupID].end())
    {
        serviceGroupMembers[serviceName][groupID].push_back(userID);
    }
}

void BaseGroupLX::leaveGroup(const string& serviceName, int groupID, const string& userID)
{
    auto& members = serviceGroupMembers[serviceName][groupID];
    members.erase(remove(members.begin(), members.end(), userID), members.end());
}

vector<string> BaseGroupLX::getGroupMembers(const string& serviceName, int groupID) const
{
    auto serviceIt = serviceGroupMembers.find(serviceName);
    if (serviceIt != serviceGroupMembers.end())
    {
        auto groupIt = serviceIt->second.find(groupID);
        if (groupIt != serviceIt->second.end())
        {
            return groupIt->second;
        }
    }
    return {};
}

bool BaseGroupLX::isOwner(const string& serviceName, int groupID, const string& userID) const
{
    auto serviceIt = serviceGroupOwners.find(serviceName);
    if (serviceIt != serviceGroupOwners.end())
    {
        auto ownerIt = serviceIt->second.find(groupID);
        return ownerIt != serviceIt->second.end() && ownerIt->second == userID;
    }
    return false;
}

vector<int> BaseGroupLX::getGroups(const string& serviceName, const string& userID) const
{
    vector<int> userGroups;
    auto serviceIt = serviceGroupMembers.find(serviceName);
    if (serviceIt != serviceGroupMembers.end())
    {
        for (const auto& group : serviceIt->second)
        {
            if (find(group.second.begin(), group.second.end(), userID) != group.second.end())
            {
                userGroups.push_back(group.first);
            }
        }
    }
    return userGroups;
}

// OwnerOnlyGroupLX
void OwnerOnlyGroupLX::createGroup(const string& serviceName, int groupID, const string& ownerID)
{
    serviceGroupOwners[serviceName][groupID] = ownerID;
    serviceGroupMembers[serviceName][groupID].push_back(ownerID);
}

bool OwnerOnlyGroupLX::hasPermission(const string& serviceName, int groupID, const string& userID) const
{
    return isOwner(serviceName, groupID, userID);
}

// OwnerAndAdminGroupLX
void OwnerAndAdminGroupLX::createGroup(const string& serviceName, int groupID, const string& ownerID)
{
    serviceGroupOwners[serviceName][groupID] = ownerID;
    serviceGroupMembers[serviceName][groupID].push_back(ownerID);
}

void OwnerAndAdminGroupLX::addAdmin(const string& serviceName, int groupID, const string& userID)
{
    if (isOwner(serviceName, groupID, userID)) return; // 群主无需添加为管理员

    auto& admins = serviceGroupAdmins[serviceName][groupID];
    if (find(admins.begin(), admins.end(), userID) == admins.end())
    {
        admins.push_back(userID);
    }
}

void OwnerAndAdminGroupLX::removeAdmin(const string& serviceName, int groupID, const string& userID)
{
    auto& admins = serviceGroupAdmins[serviceName][groupID];
    admins.erase(remove(admins.begin(), admins.end(), userID), admins.end());
}

bool OwnerAndAdminGroupLX::hasPermission(const string& serviceName, int groupID, const string& userID) const
{
    if (isOwner(serviceName, groupID, userID)) return true;

    auto serviceIt = serviceGroupAdmins.find(serviceName);
    if (serviceIt != serviceGroupAdmins.end())
    {
        auto adminIt = serviceIt->second.find(groupID);
        if (adminIt != serviceIt->second.end())
        {
            const auto& admins = adminIt->second;
            return find(admins.begin(), admins.end(), userID) != admins.end();
        }
    }
    return false;
}
