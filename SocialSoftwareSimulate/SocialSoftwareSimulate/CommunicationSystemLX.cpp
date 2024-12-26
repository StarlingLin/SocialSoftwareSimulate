#include "CommunicationSystemLX.h"

using namespace std;

// ���캯��
CommunicationSystemLX::CommunicationSystemLX(GroupManagerLX* grpManager, ServiceManagerLX* srvManager)
    : groupManager(grpManager), serviceManager(srvManager)
{
}

// ϵͳ��ʼ��
void CommunicationSystemLX::initialize()
{
    cout << "���ڳ�ʼ��ͨ��ϵͳ..." << endl;

    // �����ݿ��������
    database.loadUsers(userManager);
    database.loadGroups(groupManager);
    database.loadServices(serviceManager);

    // ��ʼ����־
    logger.log("ϵͳ��ʼ���ɹ���");

    cout << "��ʼ����ɡ�" << endl;
}

// ϵͳ�������߼�
void CommunicationSystemLX::run()
{
    bool isRunning = true;
    while (isRunning)
    {
        displayMenu();
        int choice;
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            string userID, nickname;
            cout << "�������û�ID: ";
            cin >> userID;
            cout << "�������ǳ�: ";
            cin >> nickname;
            userManager.addUser(userID, nickname, "δ֪", "δ֪", "δ֪");
            logger.log("�û������: " + userID);
            break;
        }
        case 2:
        {
            string userID;
            cout << "������Ҫ�Ƴ����û�ID: ";
            cin >> userID;
            userManager.removeUser(userID);
            logger.log("�û����Ƴ�: " + userID);
            break;
        }
        case 3:
        {
            userManager.displayAllUsers();
            break;
        }
        case 4:
        {
            string serviceName;
            cout << "�������������: ";
            cin >> serviceName;
            ServiceLX* service = serviceManager->getService(serviceName);
            if (service)
            {
                service->displayServiceInfo();
            }
            else
            {
                cout << "δ�ҵ�ָ������" << endl;
            }
            break;
        }
        case 5:
        {
            string userID, friendID;
            cout << "�����������û�ID: ";
            cin >> userID;
            cout << "������Ҫ��ӵĺ����û�ID: ";
            cin >> friendID;
            if (userManager.userExists(userID) && userManager.userExists(friendID))
            {
                ServiceLX* qqService = serviceManager->getService("QQ");
                if (qqService)
                {
                    qqService->addFriend(userID, friendID);
                    logger.log("���������: " + friendID + " ���û�: " + userID);
                    cout << "������ӳɹ���" << endl;
                }
            }
            else
            {
                cout << "�û�ID��Ч��" << endl;
            }
            break;
        }
        case 6:
        {
            int groupID;
            string userID;
            cout << "������Ⱥ��ID: ";
            cin >> groupID;
            cout << "�����������û�ID�Լ���Ⱥ��: ";
            cin >> userID;
            if (userManager.userExists(userID))
            {
                groupManager->joinGroup(groupID, userID);
                logger.log("�û�����Ⱥ��: " + to_string(groupID));
                cout << "�ɹ�����Ⱥ�飡" << endl;
            }
            else
            {
                cout << "�û�ID��Ч��" << endl;
            }
            break;
        }
        case 0:
            isRunning = false;
            break;
        default:
            cout << "��Чѡ������ԡ�" << endl;
        }
    }

    cout << "�����˳�ϵͳ..." << endl;
    logger.log("ϵͳ�˳���");
}

// ϵͳ�˳�
void CommunicationSystemLX::shutdown()
{
    cout << "���ڱ������ݲ��ر�ϵͳ..." << endl;

    // �����ݱ��浽���ݿ�
    database.saveUsers(userManager);
    database.saveGroups(groupManager);
    database.saveServices(serviceManager);

    logger.log("ϵͳ�ر���ɡ�");
}

// ���˵�
void CommunicationSystemLX::displayMenu() const
{
    cout << "\n===== ͨ��ϵͳ�˵� =====" << endl;
    cout << "1. ����û�" << endl;
    cout << "2. �Ƴ��û�" << endl;
    cout << "3. ��ʾ�����û�" << endl;
    cout << "4. ��ʾ������Ϣ" << endl;
    cout << "5. ��Ӻ���" << endl;
    cout << "6. ����Ⱥ��" << endl;
    cout << "0. �˳�" << endl;
    cout << "======================" << endl;
    cout << "������ѡ��: ";
}
