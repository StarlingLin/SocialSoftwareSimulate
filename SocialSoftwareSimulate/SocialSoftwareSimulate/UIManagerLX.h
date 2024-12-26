#pragma once

#include <stack>
#include <string>
#include <iostream>
#include "UserLX.h"
#include "LoggerLX.h"
#include "ManagerLX.h"
#include "DatabaseLX.h"
#include "FriendLX.h"
#include "GroupLX.h"

using namespace std;

class UIManagerLX
{
private:
    stack<string> pageStack;          // ҳ��ջ�����ڹ�������л�
    LoggerLX* logger;                 // ��־������
    UserManagerLX* userManager;       // �û�������
    ServiceManagerLX* serviceManager; // ���������
    GroupManagerLX* groupManager;     // Ⱥ�������
    FriendLX friendManager;           // ���ѹ�����
    DatabaseLX* database;             // ���ݿ������

    string currentService;            // ��ǰ����ķ�������
    string loggedInUser;              // ��ǰ��¼���û���

    void displayMainMenu();           // ��ʾ���˵�
    void displayLoginMenu();          // ��ʾ��¼����
    void displayRegisterMenu();       // ��ʾע�����
    void displayServiceSelectionMenu(); // ��ʾ����ѡ��˵�
    void displayServiceMenu();        // ��ʾ����˵�
    void displayUserManagementMenu(); // ��ʾ�û�����˵�
    void displayGroupManagementMenu();// ��ʾȺ�����˵�

    void displayUserInfo();           // ��ʾ�û���Ϣ
    void modifyUserInfo();            // �޸��û���Ϣ

public:
    UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database);

    void start();                     // �������������
};
