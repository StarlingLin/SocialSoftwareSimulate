#include "DatabaseLX.h"
#include <fstream>
#include <iostream>

using namespace std;

// 加载用户数据
void DatabaseLX::loadUsers(UserManagerLX& userManager)
{
    ifstream inFile("users.txt");
    if (!inFile)
    {
        cout << "无法打开用户数据文件进行加载。" << endl;
        return;
    }

    string userID, nickname, birthDate, tAge, location;
    while (inFile >> userID >> nickname >> birthDate >> tAge >> location)
    {
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

    for (const auto& user : userManager.getAllUsers())
    {
        outFile << user.first << " " << user.second.getNickname() << " "
            << user.second.getBirthDate() << " " << user.second.getTAge() << " "
            << user.second.getLocation() << endl;
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
        cout << "无法打开群组数据文件进行加载。" << endl;
        return;
    }

    int groupID;
    string userID;
    while (inFile >> groupID >> userID)
    {
        groupManager->joinGroup(groupID, userID);
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
        for (const auto& member : group.second)
        {
            outFile << group.first << " " << member << endl;
        }
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
        cout << "无法打开服务数据文件进行加载。" << endl;
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
    cout << "服务数据保存完成。" << endl;
}
