#include "DatabaseLX.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// �����û�����
void DatabaseLX::loadUsers(UserManagerLX& userManager)
{
    ifstream inFile("users.txt");
    if (!inFile)
    {
        cout << "�û������ļ������ڣ�����������" << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string userID, nickname, birthDate, tAge, location;
        getline(ss, userID, ',');
        getline(ss, nickname, ',');
        getline(ss, birthDate, ',');
        getline(ss, tAge, ',');
        getline(ss, location, ',');

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

    for (const auto& userPair : userManager.getAllUsers())
    {
        const UserLX& user = userPair.second;
        outFile << user.getQQID() << ","
            << user.getNickname() << ","
            << user.getBirthDate() << ","
            << user.getTAge() << ","
            << user.getLocation() << endl;
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
        cout << "Ⱥ�������ļ������ڣ�����������" << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        int groupID;
        ss >> groupID;

        vector<string> members;
        string memberID;
        while (ss >> memberID)
        {
            members.push_back(memberID);
        }

        groupManager->createGroup(groupID);
        for (const auto& member : members)
        {
            groupManager->joinGroup(groupID, member);
        }
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
        outFile << group.first;
        for (const auto& member : group.second)
        {
            outFile << " " << member;
        }
        outFile << endl;
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
        cout << "���������ļ������ڣ�����������" << endl;
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string serviceName, isActiveStr, usersStr;
        getline(ss, serviceName, ',');
        getline(ss, isActiveStr, ',');
        getline(ss, usersStr, ',');

        bool isActive = (isActiveStr == "true");
        vector<string> users;

        stringstream usersSS(usersStr);
        string userID;
        while (getline(usersSS, userID, ';'))
        {
            users.push_back(userID);
        }

        ServiceLX* service = new ServiceLX(serviceName, isActive);
        for (const auto& user : users)
        {
            service->loginUser(user);
        }

        serviceManager->addService(serviceName, service);
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
        const ServiceLX* service = servicePair.second;
        outFile << service->getServiceName() << ","
            << (service->isActive() ? "true" : "false") << ",";

        const auto& users = service->getLoggedUsers();
        for (size_t i = 0; i < users.size(); ++i)
        {
            outFile << users[i];
            if (i < users.size() - 1)
            {
                outFile << ";";
            }
        }
        outFile << endl;
    }

    outFile.close();
    cout << "�������ݱ�����ɡ�" << endl;
}
