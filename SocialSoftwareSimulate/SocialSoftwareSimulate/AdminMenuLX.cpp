// AdminMenuLX.cpp
#include "AdminMenuLX.h"
#include <iostream>

using namespace std;

// ��ʾ��̨�������˵�
void AdminMenuLX::showMainMenu()
{
    int choice = -1;
    pageStack.push(0); // ���˵�ҳ����Ϊ 0

    while (!pageStack.empty())
    {
        int currentPage = pageStack.top();

        switch (currentPage)
        {
        case 0: // ���˵�
            cout << "\n--- ��̨�������˵� ---\n";
            cout << "1. �û�����\n2. Ⱥ�����\n3. �������\n4. ��Ϣ����\n5. �˳�\n";
            choice = getUserInput();

            if (choice == 1) navigateTo(1);
            else if (choice == 2) navigateTo(2);
            else if (choice == 3) navigateTo(3);
            else if (choice == 4) navigateTo(4);
            else if (choice == 5) goBack();
            break;

        case 1: // �û�����˵�
            userManagementMenu();
            break;

        case 2: // Ⱥ�����˵�
            groupManagementMenu();
            break;

        case 3: // �������˵�
            serviceManagementMenu();
            break;

        case 4: // ��Ϣ����˵�
            messageManagementMenu();
            break;
        }
    }
}

// �û�����˵�
void AdminMenuLX::userManagementMenu()
{
    cout << "\n--- �û����� ---\n";
    cout << "����δʵ��\n";
    goBack();
}

// Ⱥ�����˵�
void AdminMenuLX::groupManagementMenu()
{
    cout << "\n--- Ⱥ����� ---\n";
    cout << "����δʵ��\n";
    goBack();
}

// �������˵�
void AdminMenuLX::serviceManagementMenu()
{
    cout << "\n--- ������� ---\n";
    cout << "����δʵ��\n";
    goBack();
}

// ��Ϣ����˵�
void AdminMenuLX::messageManagementMenu()
{
    cout << "\n--- ��Ϣ���� ---\n";
    cout << "����δʵ��\n";
    goBack();
}

// ������ָ��ҳ��
void AdminMenuLX::navigateTo(int pageID)
{
    system("cls");
    pageStack.push(pageID);
}

// ������һ��ҳ��
void AdminMenuLX::goBack()
{
    system("cls");
    if (!pageStack.empty())
    {
        pageStack.pop();
    }
    if (pageStack.empty())
    {
        cout << "\n���˳���̨����ϵͳ��\n";
        exit(0);
    }
}

// ���������������û�����
int AdminMenuLX::getUserInput()
{
    int choice;
    cout << "������ѡ�";
    cin >> choice;
    return choice;
}
