#pragma once

#include <string>
#include <iostream>
#include "ManagerLX.h"
#include "DatabaseLX.h"
#include "LoggerLX.h"

using namespace std;

class CommunicationSystemLX 
{
private:
    UserManagerLX userManager;        // �û�������
    GroupManagerLX* groupManager;    // Ⱥ�����������ָ��
    ServiceManagerLX* serviceManager; // �������������ָ��
    DatabaseLX database;             // ���ݿ�
    LoggerLX logger;                 // ��־��¼��

public:
    CommunicationSystemLX(GroupManagerLX* grpManager, ServiceManagerLX* srvManager);

    // ϵͳ��ʼ��
    void initialize();

    // ϵͳ�������߼�
    void run();

    // ϵͳ�˳�
    void shutdown();

    // ���˵�
    void displayMenu() const;
};
