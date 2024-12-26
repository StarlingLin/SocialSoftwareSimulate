#pragma once

#include <string>
#include "ManagerLX.h"

using namespace std;

class DatabaseLX
{
public:
    // 加载用户数据
    void loadUsers(UserManagerLX& userManager);

    // 保存用户数据
    void saveUsers(const UserManagerLX& userManager);

    // 加载群组数据
    void loadGroups(GroupManagerLX* groupManager);

    // 保存群组数据
    void saveGroups(const GroupManagerLX* groupManager);

    // 加载服务数据
    void loadServices(ServiceManagerLX* serviceManager);

    // 保存服务数据
    void saveServices(const ServiceManagerLX* serviceManager);
};
