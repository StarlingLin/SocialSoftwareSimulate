#pragma once

#include <stack>
#include <string>
#include <map>
#include <vector>

using namespace std;

class UserMenuLX
{
private:
    stack<int> pageStack; // ҳ��ջ�����ڹ���˵�����
    string currentService; // ��ǰ��¼�ķ�������
    string currentUserID; // ��ǰ��¼���û�ID
    map<string, map<string, string>> authInfo; // ������ -> �û�ID -> ����
    map<string, vector<string>> friendData; // ������ -> �����б�
    map<string, vector<string>> groupData;  // ������ -> Ⱥ���б�

public:
    // ��ʾ��¼ҳ��
    void showLoginPage();

    // �û�ע��ҳ��
    void showRegisterPage();

    // ��֤��¼��Ϣ
    bool validateLogin(const string& serviceName, const string& userID, const string& password);

    // �����û���֤��Ϣ���ļ�
    void saveAllAuthInfo();

    // �����û���֤��Ϣ
    void saveAuthInfo(const string& serviceName, const string& userID, const string& password);

    // �����û���֤��Ϣ
    void loadAuthInfo();

    // ���ط����������
    void loadServiceData(const string& serviceName, const string& userID);

    // ��������������
    void saveServiceData(const string& serviceName);

    // ��ʾ������ҳ��
    void showServiceMainPage();

    // ���ѹ���ҳ��
    void showFriendMenu();

    // Ⱥ�����ҳ��
    void showGroupMenu();

    // �޸ĸ�����Ϣҳ��
    void showEditProfilePage();

    // ע���˻�ҳ��
    void showDeleteAccountPage();

    // ������ָ��ҳ��
    void navigateTo(int pageID);

    // ������һ��ҳ��
    void goBack();

    // ���������������û�����
    int getUserInput();
};
