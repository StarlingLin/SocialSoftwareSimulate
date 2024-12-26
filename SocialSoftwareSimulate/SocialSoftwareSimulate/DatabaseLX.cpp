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
        string userID, serviceName, nickname;
        getline(ss, userID, ',');
        getline(ss, serviceName, ',');
        getline(ss, nickname, ',');

        bool useQQID = nickname.empty(); // 如果昵称为空，认为使用 QQID
        serviceManager->registerService(userID, serviceName, !useQQID, nickname);
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
                outFile << userID << "," << service->getServiceName() << "," << service->getNickname(userID) << endl;
            }
        }
    }

    outFile.close();
    cout << "服务数据保存完成。" << endl;
}
