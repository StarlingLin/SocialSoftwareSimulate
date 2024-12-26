#pragma once

#include <stack>
#include <string>
#include <iostream>
#include "LoggerLX.h"
#include "ManagerLX.h"

using namespace std;

class UIManagerLX
{
private:
    stack<string> pageStack;          // ҳ��ջ�����ڹ�������л�
    LoggerLX* logger;                 // ��־������
    UserManagerLX* userManager;       // �û�������
    ServiceManagerLX* serviceManager; // ���������
    GroupManagerLX* groupManager;     // Ⱥ�������

    void displayMainMenu();           // ��ʾ���˵�
    void displayLoginMenu();          // ��ʾ��¼����
    void displayRegisterMenu();       // ��ʾע�����
    void displayServiceSelectionMenu(); // ��ʾ����ѡ��˵�
    void displayServiceMenu();        // ��ʾ����˵�
    void displayUserManagementMenu(); // ��ʾ�û�����˵�
    void displayGroupManagementMenu();// ��ʾȺ�����˵�

public:
    UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager);

    void start();                     // �������������
};
