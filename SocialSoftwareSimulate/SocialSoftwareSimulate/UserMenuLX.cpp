#include "UserMenuLX.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

// ��ʾ��¼ҳ��
void UserMenuLX::showLoginPage()
{
    string serviceName;
    string userID;
    string password;

    cout << "\n--- �û���¼ ---\n";
    cout << "������������ƣ��� QQ �� ΢�ţ���";
    cin >> serviceName;
    cout << "�������û�ID��";
    cin >> userID;
    cout << "���������룺";
    cin >> password;

    if (validateLogin(serviceName, userID, password))
    {
        cout << "��¼�ɹ���\n";
        currentService = serviceName; // ���õ�ǰ����
        currentUserID = userID;       // ���õ�ǰ�û�ID

        // ���ط����������
        loadServiceData(serviceName, userID);

        navigateTo(0);                // ������������ҳ��
        showServiceMainPage();
    }
    else
    {
        cout << "��¼ʧ�ܣ������ԡ�\n";
        showLoginPage();
    }
}

// �û�ע��ҳ��
void UserMenuLX::showRegisterPage()
{
    string serviceName;
    string userID;
    string password;
    string nickname;
    string birthDate;
    string location;
    string registrationDate;

    cout << "\n--- �û�ע�� ---\n";
    cout << "������������ƣ��� QQ �� ΢�ţ���";
    cin >> serviceName;
    cout << "�������û�ID��";
    cin >> userID;

    // ����û��Ƿ��Ѵ���
    if (authInfo[serviceName].find(userID) != authInfo[serviceName].end())
    {
        cout << "�û��Ѵ��ڣ���ֱ�ӵ�¼��\n";
        showLoginPage();
        return;
    }

    cout << "���������룺";
    cin >> password;
    cout << "�������ǳƣ�";
    cin >> nickname;
    cout << "������������ڣ���ʽ YYYY-MM-DD����";
    cin >> birthDate;
    cout << "���������ڵأ�";
    cin >> location;

    // ��ȡ��ǰ������Ϊע������
    registrationDate = "2024-12-26"; // ���赱ǰ����

    // �����û���֤��Ϣ
    saveAuthInfo(serviceName, userID, password);

    // �����û��� users.txt
    ofstream usersFile("users.txt", ios::app);
    if (usersFile.is_open())
    {
        usersFile << currentUserID << " "    // QQ ID (ͳһID)
            << serviceName << " "      // ����ID
            << userID << " "          // �û��ڷ����ID
            << nickname << " "        // �ǳ�
            << birthDate << " "       // ��������
            << registrationDate << " " // ��������ʱ��
            << location << endl;       // ���ڵ�
        usersFile.close();
        cout << "�û���Ϣ�ѱ��浽 users.txt��\n";
    }
    else
    {
        cerr << "�޷��� users.txt ���б��档\n";
    }

    cout << "ע��ɹ������¼��\n";
    showLoginPage();
}

// ��֤��¼��Ϣ
bool UserMenuLX::validateLogin(const string& serviceName, const string& userID, const string& password)
{
    auto serviceIt = authInfo.find(serviceName);
    if (serviceIt != authInfo.end())
    {
        auto userIt = serviceIt->second.find(userID);
        if (userIt != serviceIt->second.end() && userIt->second == password)
        {
            return true;
        }
    }
    return false;
}

// �����û���֤��Ϣ���ļ�
void UserMenuLX::saveAllAuthInfo()
{
    ofstream outFile("passwd.txt");
    if (!outFile.is_open())
    {
        cerr << "�޷����ļ� passwd.txt ����д�롣\n";
        return;
    }

    for (const auto& service : authInfo)
    {
        for (const auto& user : service.second)
        {
            outFile << service.first << " " << user.first << " " << user.second << endl;
        }
    }

    outFile.close();
    cout << "�û���֤��Ϣ�ѱ��档\n";
}

// �����û���֤��Ϣ
void UserMenuLX::saveAuthInfo(const string& serviceName, const string& userID, const string& password)
{
    authInfo[serviceName][userID] = password;

    saveAllAuthInfo(); // ����ȫ����֤��Ϣ���ļ�
}

// �����û���֤��Ϣ
void UserMenuLX::loadAuthInfo()
{
    ifstream inFile("passwd.txt");
    if (!inFile.is_open())
    {
        cerr << "�޷����ļ� passwd.txt ���ж�ȡ��\n";
        return;
    }

    string line;
    while (getline(inFile, line))
    {
        stringstream ss(line);
        string serviceName, userID, password;
        ss >> serviceName >> userID >> password;
        authInfo[serviceName][userID] = password;
    }

    inFile.close();
}

// ���ط����������
void UserMenuLX::loadServiceData(const string& serviceName, const string& userID)
{
    cout << "���� " << serviceName << " ����ĺ��Ѻ�Ⱥ������...\n";

    string friendsFile = serviceName + "_friends.txt";
    string groupsFile = serviceName + "_groups.txt";

    ifstream friendsStream(friendsFile);
    ifstream groupsStream(groupsFile);

    friendData[serviceName].clear();
    groupData[serviceName].clear();

    if (friendsStream.is_open())
    {
        string friendID;
        while (getline(friendsStream, friendID))
        {
            friendData[serviceName].push_back(friendID);
        }
        friendsStream.close();
        cout << "�������ݼ��سɹ���\n";
    }
    else
    {
        cout << "���������ļ�δ�ҵ���Ĭ�ϼ���Ϊ�ա�\n";
    }

    if (groupsStream.is_open())
    {
        string groupID;
        while (getline(groupsStream, groupID))
        {
            groupData[serviceName].push_back(groupID);
        }
        groupsStream.close();
        cout << "Ⱥ�����ݼ��سɹ���\n";
    }
    else
    {
        cout << "Ⱥ�������ļ�δ�ҵ���Ĭ�ϼ���Ϊ�ա�\n";
    }
}

// ��������������
void UserMenuLX::saveServiceData(const string& serviceName)
{
    cout << "���� " << serviceName << " ���������...\n";

    string friendsFile = serviceName + "_friends.txt";
    string groupsFile = serviceName + "_groups.txt";

    ofstream friendsStream(friendsFile);
    if (friendsStream.is_open())
    {
        for (const string& friendID : friendData[serviceName])
        {
            friendsStream << friendID << endl;
        }
        friendsStream.close();
        cout << "�������ݱ���ɹ���\n";
    }
    else
    {
        cerr << "�޷��򿪺��������ļ�����д�롣\n";
    }

    ofstream groupsStream(groupsFile);
    if (groupsStream.is_open())
    {
        for (const string& groupID : groupData[serviceName])
        {
            groupsStream << groupID << endl;
        }
        groupsStream.close();
        cout << "Ⱥ�����ݱ���ɹ���\n";
    }
    else
    {
        cerr << "�޷���Ⱥ�������ļ�����д�롣\n";
    }
}

// ��ʾ������ҳ��
void UserMenuLX::showServiceMainPage()
{
    int choice = -1;
    pageStack.push(0); // ������ҳ����Ϊ 0

    while (!pageStack.empty())
    {
        int currentPage = pageStack.top();

        switch (currentPage)
        {
        case 0: // ������ҳ��
            cout << "\n--- " << currentService << " ��ҳ�� ---\n";
            cout << "1. ���ѹ���\n";
            cout << "2. Ⱥ�����\n";
            cout << "3. �޸ĸ�����Ϣ\n";
            cout << "4. ע���˻�\n";
            cout << "5. �˳�����\n";
            choice = getUserInput();

            if (choice == 1) navigateTo(1);
            else if (choice == 2) navigateTo(2);
            else if (choice == 3) navigateTo(3);
            else if (choice == 4) navigateTo(4);
            else if (choice == 5) goBack();
            break;

        case 1: // ���ѹ���ҳ��
            showFriendMenu();
            break;

        case 2: // Ⱥ�����ҳ��
            showGroupMenu();
            break;

        case 3: // �޸ĸ�����Ϣҳ��
            showEditProfilePage();
            break;

        case 4: // ע���˻�ҳ��
            showDeleteAccountPage();
            break;
        }
    }
}

// ���ѹ���ҳ��
void UserMenuLX::showFriendMenu()
{
    cout << "\n--- " << currentService << " ���ѹ��� ---\n";
    cout << "��ǰ�����б�:\n";

    if (friendData[currentService].empty())
    {
        cout << "���޺��ѡ�\n";
    }
    else
    {
        for (const string& friendID : friendData[currentService])
        {
            cout << "����: " << friendID << "\n";
        }
    }

    cout << "\n1. ������һҳ\n";
    int choice = getUserInput();
    if (choice == 1)
    {
        goBack();
    }
}

// Ⱥ�����ҳ��
void UserMenuLX::showGroupMenu()
{
    cout << "\n--- " << currentService << " Ⱥ����� ---\n";
    cout << "��ǰȺ���б�:\n";

    if (groupData[currentService].empty())
    {
        cout << "����Ⱥ�顣\n";
    }
    else
    {
        for (const string& groupID : groupData[currentService])
        {
            cout << "Ⱥ��: " << groupID << "\n";
        }
    }

    cout << "\n1. ������һҳ\n";
    int choice = getUserInput();
    if (choice == 1)
    {
        goBack();
    }
}

// �޸ĸ�����Ϣҳ��
void UserMenuLX::showEditProfilePage()
{
    string newNickname, newPassword, newLocation;

    cout << "\n--- �޸ĸ�����Ϣ ---\n";
    cout << "�������µ��ǳƣ�";
    cin >> newNickname;
    cout << "�������µ����룺";
    cin >> newPassword;
    cout << "�������µ����ڵأ�";
    cin >> newLocation;

    // �����û�������Ϣ
    authInfo[currentService][currentUserID] = newPassword;

    // ���²������û���Ϣ�� users.txt
    vector<string> updatedUsers;
    ifstream usersFile("users.txt");
    string line;

    while (getline(usersFile, line))
    {
        stringstream ss(line);
        string qqID, serviceName, userID, nickname, birthDate, tAge, location;
        ss >> qqID >> serviceName >> userID >> nickname >> birthDate >> tAge >> location;

        if (serviceName == currentService && userID == currentUserID)
        {
            updatedUsers.push_back(qqID + " " + serviceName + " " + userID + " " + newNickname + " " + birthDate + " " + tAge + " " + newLocation);
        }
        else
        {
            updatedUsers.push_back(line);
        }
    }
    usersFile.close();

    ofstream outFile("users.txt", ios::trunc);
    for (const string& updatedLine : updatedUsers)
    {
        outFile << updatedLine << endl;
    }
    outFile.close();

    // ���浽�����ļ�
    saveAllAuthInfo();

    cout << "������Ϣ�޸ĳɹ���\n";
    goBack();
}

// ע���˻�ҳ��
void UserMenuLX::showDeleteAccountPage()
{
    string confirmation;

    cout << "\n--- ע���˻� ---\n";
    cout << "ȷ��ע����ǰ�˻�����yes/no����";
    cin >> confirmation;

    if (confirmation == "yes")
    {
        // ���ڴ���ɾ���û�����
        authInfo[currentService].erase(currentUserID);

        // ���� users.txt �ļ�
        vector<string> updatedUsers;
        ifstream usersFile("users.txt");
        string line;

        while (getline(usersFile, line))
        {
            stringstream ss(line);
            string qqID, serviceName, userID, nickname, birthDate, tAge, location;
            ss >> qqID >> serviceName >> userID >> nickname >> birthDate >> tAge >> location;

            if (!(serviceName == currentService && userID == currentUserID))
            {
                updatedUsers.push_back(line);
            }
        }
        usersFile.close();

        ofstream outFile("users.txt", ios::trunc);
        for (const string& updatedLine : updatedUsers)
        {
            outFile << updatedLine << endl;
        }
        outFile.close();

        // ���浽�����ļ�
        saveAllAuthInfo();

        cout << "�˻���ע����\n";
        goBack();
    }
    else
    {
        cout << "ȡ��ע��������\n";
        goBack();
    }
}

// ���������������û�����
int UserMenuLX::getUserInput()
{
    int choice;
    cout << "������ѡ�";
    cin >> choice;
    return choice;
}

// ������ָ��ҳ��
void UserMenuLX::navigateTo(int pageID)
{
    system("cls");
    pageStack.push(pageID);
}

// ������һ��ҳ��
void UserMenuLX::goBack()
{
    system("cls");
    if (!pageStack.empty())
    {
        pageStack.pop();
    }

    if (pageStack.empty())
    {
        saveServiceData(currentService);
        cout << "\n���˳��û�ϵͳ��\n";
        exit(0);
    }
}
