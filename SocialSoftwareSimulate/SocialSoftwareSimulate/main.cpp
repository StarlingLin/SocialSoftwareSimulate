#include <iostream>
#include "AdminMenuLX.h"
#include "UserMenuLX.h"
#include "FileLX.h"

using namespace std;

int main()
{
    // ��ʼ���û��˵����ļ�����ģ��
    UserMenuLX userMenu;
    FileLX fileHandler;

    // �����û���֤��Ϣ
    userMenu.loadAuthInfo();

    // ����������������
    auto userData = fileHandler.loadCompleteUserData("users.txt");
    auto groupData = fileHandler.loadGroupData("groups.txt");
    auto friendData = fileHandler.loadFriendData("friends.txt");
    auto serviceData = fileHandler.loadServiceData("services.txt");

    cout << "���ݼ��سɹ���\n";

    // ���˵�ѡ��
    int choice;
    cout << "��ѡ��ģʽ��\n";
    cout << "1. ��̨����ҳ��\n";
    cout << "2. �û���¼ҳ��\n";
    cout << "3. �û�ע��ҳ��\n";
    cin >> choice;

    system("cls");

    if (choice == 1)
    {
        AdminMenuLX adminMenu;
        adminMenu.showMainMenu();
    }
    else if (choice == 2)
    {
        userMenu.showLoginPage();
    }
    else if (choice == 3)
    {
        userMenu.showRegisterPage();
    }
    else
    {
        cout << "��Чѡ�񣬳����˳���\n";
    }

    // ��������
    fileHandler.saveCompleteUserData("users.txt", userData);
    fileHandler.saveGroupData("groups.txt", groupData);
    fileHandler.saveFriendData("friends.txt", friendData);
    fileHandler.saveServiceData("services.txt", serviceData);

    cout << "���ݱ���ɹ���\n";

    return 0;
}
