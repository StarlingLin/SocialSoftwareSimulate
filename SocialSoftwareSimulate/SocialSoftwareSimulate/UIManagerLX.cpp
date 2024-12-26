#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager) {
}

void UIManagerLX::start()
{
    pageStack.push("Main Menu");
    while (!pageStack.empty())
    {
        string currentPage = pageStack.top();
        if (currentPage == "Main Menu")
        {
            displayMainMenu();
        }
        else if (currentPage == "Login Menu")
        {
            displayLoginMenu();
        }
        else if (currentPage == "Register Menu")
        {
            displayRegisterMenu();
        }
        else if (currentPage == "Service Selection")
        {
            displayServiceSelectionMenu();
        }
        else if (currentPage == "Service Menu")
        {
            displayServiceMenu();
        }
        else if (currentPage == "User Management")
        {
            displayUserManagementMenu();
        }
        else if (currentPage == "Group Management")
        {
            displayGroupManagementMenu();
        }
    }
}

void UIManagerLX::displayMainMenu()
{
    cout << "��ӭ�����罻ģ�������" << endl;
    cout << "1. ��¼" << endl;
    cout << "2. ע��" << endl;
    cout << "3. �˳�" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        pageStack.push("Login Menu");
        logger->log("�û�ѡ���¼��");
        break;
    case 2:
        pageStack.push("Register Menu");
        logger->log("�û�ѡ��ע�ᡣ");
        break;
    case 3:
        pageStack.pop();
        logger->log("�û��˳�����");
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}

void UIManagerLX::displayLoginMenu()
{
    PasswdLX passwdManager;
    cout << "�����������û�����";
    string username;
    cin >> username;
    cout << "�������������룺";
    string password;
    cin >> password;

    if (passwdManager.validatePassword(username, password))
    {
        logger->log("�û� " + username + " �ɹ���¼��");
        cout << "��¼�ɹ���" << endl;
        pageStack.pop();
        pageStack.push("Service Selection");
    }
    else
    {
        logger->log("�û� " + username + " ��¼ʧ�ܡ�");
        cout << "�û�����������������ԡ�" << endl;
    }
}

void UIManagerLX::displayRegisterMenu()
{
    PasswdLX passwdManager;
    cout << "����������Ҫע����û�����";
    string username;
    cin >> username;
    cout << "�������������룺";
    string password;
    cin >> password;

    if (!passwdManager.userExists(username))
    {
        userManager->addUser(username, username, "2000-01-01", "1", "Ĭ��λ��");
        passwdManager.setPassword(username, password);
        logger->log("�û� " + username + " ע��ɹ���");
        cout << "ע��ɹ���" << endl;
        pageStack.pop();
    }
    else
    {
        logger->log("�û� " + username + " ע��ʧ�ܣ��û����Ѵ��ڡ�");
        cout << "�û����Ѵ��ڣ������ԡ�" << endl;
    }
}

void UIManagerLX::displayServiceSelectionMenu()
{
    cout << "��ѡ��Ҫ����ķ���" << endl;
    cout << "1. QQ����" << endl;
    cout << "2. ΢�ŷ���" << endl;
    cout << "3. ΢A����" << endl;
    cout << "4. ΢B����" << endl;
    cout << "5. �������˵�" << endl;
    int choice;
    cin >> choice;

    string username = "��ǰ��¼�û���"; // ����洢�˵�¼�û���Ϣ
    string nickname;
    switch (choice)
    {
    case 1:
        cout << "����QQ����" << endl;
        pageStack.push("Service Menu");
        break;
    case 2:
        if (!serviceManager->isServiceEnabled(username, "WeChat"))
        {
            cout << "δ��ͨ΢�ŷ����������ǳ���ע�᣺";
            cin >> nickname;
            serviceManager->registerService(username, "WeChat", true, nickname);
            logger->log("�û���ͨ��΢�ŷ���");
            cout << "΢�ŷ���ͨ�ɹ���" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 3:
        if (!serviceManager->isServiceEnabled(username, "MicroA"))
        {
            cout << "δ��ͨ΢A���񣬽�ֱ��ʹ��QQ IDע�ᡣ" << endl;
            serviceManager->registerService(username, "MicroA", false, "");
            logger->log("�û���ͨ��΢A����");
            cout << "΢A����ͨ�ɹ���" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 4:
        if (!serviceManager->isServiceEnabled(username, "MicroB"))
        {
            cout << "δ��ͨ΢B�����������ǳ���ע�᣺";
            cin >> nickname;
            serviceManager->registerService(username, "MicroB", true, nickname);
            logger->log("�û���ͨ��΢B����");
            cout << "΢B����ͨ�ɹ���" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 5:
        pageStack.pop();
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}

void UIManagerLX::displayServiceMenu()
{
    cout << "��ӭ�������˵���" << endl;
    cout << "1. �鿴������Ϣ" << endl;
    cout << "2. �鿴�����б�" << endl;
    cout << "3. �鿴Ⱥ����Ϣ" << endl;
    cout << "4. ���ط���ѡ��" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // ���þ������ĸ�����Ϣ��ʾ�߼�
        logger->log("�û��鿴�˸�����Ϣ��");
        break;
    case 2:
        // ���þ������ĺ����б���ʾ�߼�
        logger->log("�û��鿴�˺����б�");
        break;
    case 3:
        // ���þ�������Ⱥ����Ϣ��ʾ�߼�
        logger->log("�û��鿴��Ⱥ����Ϣ��");
        break;
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}
