#include "DatabaseLX.h"
#include <fstream>
#include <iostream>
#include <sstream>

using namespace std;

// 加载用户数据
void DatabaseLX::loadUsers(UserManagerLX& userManager)
{
    ifstream inFile("users.txt");
    if (!inFile)
    {
        cout << "用户数据文件不存在，加载跳过。" << endl;
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
    cout << "用户数据加载完成。" << endl;
}

// 保存用户数据
void DatabaseLX::saveUsers(const UserManagerLX& userManager)
{
    ofstream outFile("users.txt");
    if (!outFile)
    {
        cout << "无法打开用户数据文件进行保存。" << endl;
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
    cout << "用户数据保存完成。" << endl;
}

// 加载群组数据
void DatabaseLX::loadGroups(GroupManagerLX* groupManager)
{
    ifstream inFile("groups.txt");
    if (!inFile)
    {
        cout << "群组数据文件不存在，加载跳过。" << endl;
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
    cout << "群组数据加载完成。" << endl;
}

// 保存群组数据
void DatabaseLX::saveGroups(const GroupManagerLX* groupManager)
{
    ofstream outFile("groups.txt");
    if (!outFile)
    {
        cout << "无法打开群组数据文件进行保存。" << endl;
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
    cout << "群组数据保存完成。" << endl;
}

// 加载服务数据
void DatabaseLX::loadServices(ServiceManagerLX* serviceManager)
{
    ifstream inFile("services.txt");
    if (!inFile)
    {
        cout << "服务数据文件不存在，加载跳过。" << endl;
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
    cout << "服务数据加载完成。" << endl;
}

// 保存服务数据
void DatabaseLX::saveServices(const ServiceManagerLX* serviceManager)
{
    ofstream outFile("services.txt");
    if (!outFile)
    {
        cout << "无法打开服务数据文件进行保存。" << endl;
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
    cout << "服务数据保存完成。" << endl;
}
