#pragma once

#include <stack>

using namespace std;

class AdminMenuLX
{
private:
    stack<int> pageStack; // ҳ��ջ�����ڹ���˵�����

public:
    // ��ʾ��̨�������˵�
    void showMainMenu();

    // �û�����˵�
    void userManagementMenu();

    // Ⱥ�����˵�
    void groupManagementMenu();

    // �������˵�
    void serviceManagementMenu();

    // ��Ϣ����˵�
    void messageManagementMenu();

    // ������ָ��ҳ��
    void navigateTo(int pageID);

    // ������һ��ҳ��
    void goBack();

    // ���������������û�����
    int getUserInput();
};
