#include "DatabaseLX.h"
#include <fstream>
#include <iostream>

using namespace std;

// �����û�����
void DatabaseLX::loadUsers(UserManagerLX& userManager)
{
    ifstream inFile("users.txt");
    if (!inFile)
    {
        cout << "�޷����û������ļ����м��ء�" << endl;
        return;
    }

    string userID, nickname, birthDate, tAge, location;
    while (inFile >> userID >> nickname >> birthDate >> tAge >> location)
    {
        userManager.addUser(userID, nickname, birthDate, tAge, location);
    }

    inFile.close();
    cout << "�û����ݼ�����ɡ�" << endl;
}

// �����û�����
void DatabaseLX::saveUsers(const UserManagerLX& userManager)
{
    ofstream outFile("users.txt");
    if (!outFile)
    {
        cout << "�޷����û������ļ����б��档" << endl;
        return;
    }

    for (const auto& user : userManager.getAllUsers())
    {
        outFile << user.first << " " << user.second.getNickname() << " "
            << user.second.getBirthDate() << " " << user.second.getTAge() << " "
            << user.second.getLocation() << endl;
    }

    outFile.close();
    cout << "�û����ݱ�����ɡ�" << endl;
}

// ����Ⱥ������
void DatabaseLX::loadGroups(GroupManagerLX* groupManager)
{
    ifstream inFile("groups.txt");
    if (!inFile)
    {
        cout << "�޷���Ⱥ�������ļ����м��ء�" << endl;
        return;
    }

    int groupID;
    string userID;
    while (inFile >> groupID >> userID)
    {
        groupManager->joinGroup(groupID, userID);
    }

    inFile.close();
    cout << "Ⱥ�����ݼ�����ɡ�" << endl;
}

// ����Ⱥ������
void DatabaseLX::saveGroups(const GroupManagerLX* groupManager)
{
    ofstream outFile("groups.txt");
    if (!outFile)
    {
        cout << "�޷���Ⱥ�������ļ����б��档" << endl;
        return;
    }

    for (const auto& group : groupManager->getAllGroups())
    {
        for (const auto& member : group.second)
        {
            outFile << group.first << " " << member << endl;
        }
    }

    outFile.close();
    cout << "Ⱥ�����ݱ�����ɡ�" << endl;
}

// ���ط�������
void DatabaseLX::loadServices(ServiceManagerLX* serviceManager)
{
    ifstream inFile("services.txt");
    if (!inFile)
    {
        cout << "�޷��򿪷��������ļ����м��ء�" << endl;
        return;
    }

    string userID, serviceName, nickname;
    while (inFile >> userID >> serviceName >> nickname)
    {
        ServiceLX* service = serviceManager->getService(serviceName);
        if (service)
        {
            service->registerUser(userID, nickname);
        }
    }

    inFile.close();
    cout << "�������ݼ�����ɡ�" << endl;
}

// �����������
void DatabaseLX::saveServices(const ServiceManagerLX* serviceManager)
{
    ofstream outFile("services.txt");
    if (!outFile)
    {
        cout << "�޷��򿪷��������ļ����б��档" << endl;
        return;
    }

    for (const auto& servicePair : serviceManager->getAllServices())
    {
        ServiceLX* service = servicePair.second;
        if (service)
        {
            for (const auto& userID : service->getAllBoundUsers())
            {
                outFile << userID << " " << service->getServiceName() << " " << service->getNickname(userID) << endl;
            }
        }
    }

    outFile.close();
    cout << "�������ݱ�����ɡ�" << endl;
}
