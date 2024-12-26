#pragma once

#include <string>
#include "ManagerLX.h"

using namespace std;

class DatabaseLX
{
public:
    // �����û�����
    void loadUsers(UserManagerLX& userManager);

    // �����û�����
    void saveUsers(const UserManagerLX& userManager);

    // ����Ⱥ������
    void loadGroups(GroupManagerLX* groupManager);

    // ����Ⱥ������
    void saveGroups(const GroupManagerLX* groupManager);

    // ���ط�������
    void loadServices(ServiceManagerLX* serviceManager);

    // �����������
    void saveServices(const ServiceManagerLX* serviceManager);
};
