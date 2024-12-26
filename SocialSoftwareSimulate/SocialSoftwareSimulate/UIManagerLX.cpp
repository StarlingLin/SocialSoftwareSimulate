#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager), database(database), currentService(""), loggedInUser("") {
}

void UIManagerLX::start()
{
    // ���ط�������
    database->loadServices(serviceManager);

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

    // �˳�ǰ�����������
    database->saveServices(serviceManager);
}

void UIManagerLX::displayMainMenu()
{
    system("cls");
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
    system("cls");
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
        loggedInUser = username;
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
    system("cls");
    PasswdLX passwdManager;
    cout << "����������Ҫע����û�����";
    string username;
    cin >> username;
    cout << "�������������룺";
    string password;
    cin >> password;
    cout << "�����������ǳƣ�";
    string nickname;
    cin >> nickname;

    if (!passwdManager.userExists(username))
    {
        userManager->addUser(username, nickname, "2000-01-01", "1", "Ĭ��λ��");
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
    system("cls");
    cout << "��ѡ��Ҫ����ķ���" << endl;
    cout << "1. QQ����" << endl;
    cout << "2. ΢�ŷ���" << endl;
    cout << "3. ΢A����" << endl;
    cout << "4. ΢B����" << endl;
    cout << "5. �������˵�" << endl;
    int choice;
    cin >> choice;

    string nickname;
    string id;
    switch (choice)
    {
    case 1:
        currentService = "QQ";
        pageStack.push("Service Menu");
        break;
    case 2:
        currentService = "WeChat";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "δ��ͨ΢�ŷ������������ID��";
            cin >> id;
            cout << "�������ǳƣ�";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, true, nickname);

            database->saveServices(serviceManager);

            logger->log("�û���ͨ��΢�ŷ���");
            cout << "΢�ŷ���ͨ�ɹ���" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 3:
        currentService = "MicroA";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "δ��ͨ΢A�����������ǳƣ�";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, false, nickname);

            database->saveServices(serviceManager);

            logger->log("�û���ͨ��΢A����");
            cout << "΢A����ͨ�ɹ���" << endl;
        }
        pageStack.push("Service Menu");
        break;
    case 4:
        currentService = "MicroB";
        if (!serviceManager->isServiceEnabled(loggedInUser, currentService))
        {
            cout << "δ��ͨ΢B�������������ID��";
            cin >> id;
            cout << "�������ǳƣ�";
            cin >> nickname;
            serviceManager->registerService(loggedInUser, currentService, true, nickname);

            database->saveServices(serviceManager);

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
    system("cls");
    cout << "��ӭ���� " << currentService << " ����˵���" << endl;
    cout << "1. �鿴������Ϣ" << endl;
    cout << "2. �鿴�����б�" << endl;
    cout << "3. �鿴Ⱥ����Ϣ" << endl;
    cout << "4. ���ط���ѡ��" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        cout << "������Ϣ��" << endl;
        cout << "�ǳ�: " << serviceManager->getService(currentService)->getNickname(loggedInUser) << endl;
        logger->log("�û��鿴�˸�����Ϣ��");
        break;
    case 2:
        cout << "�����б�" << endl;
        for (const string& friendID : serviceManager->getService(currentService)->getFriends(loggedInUser))
        {
            cout << friendID << endl;
        }
        logger->log("�û��鿴�˺����б�");
        break;
    case 3:
        cout << "Ⱥ����Ϣ��" << endl;
        for (int groupID : serviceManager->getService(currentService)->getGroups(loggedInUser))
        {
            cout << "Ⱥ��ID: " << groupID << endl;
        }
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

void UIManagerLX::displayUserManagementMenu()
{
    system("cls");
    cout << "\n===== �û�����˵� =====" << endl;
    cout << "1. ����û�" << endl;
    cout << "2. �Ƴ��û�" << endl;
    cout << "3. ��ʾ�����û�" << endl;
    cout << "0. �������˵�" << endl;
    cout << "=======================" << endl;
    cout << "������ѡ��: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // ��������û��߼�
        break;
    case 2:
        // �����Ƴ��û��߼�
        break;
    case 3:
        // ������ʾ�����û��߼�
        break;
    case 0:
        return;
    default:
        cout << "��Чѡ������ԡ�" << endl;
        break;
    }
}

void UIManagerLX::displayGroupManagementMenu()
{
    system("cls");
    cout << "\n===== Ⱥ�����˵� =====" << endl;
    cout << "1. ����Ⱥ��" << endl;
    cout << "2. ��ɢȺ��" << endl;
    cout << "3. ��ʾ����Ⱥ��" << endl;
    cout << "0. �������˵�" << endl;
    cout << "=======================" << endl;
    cout << "������ѡ��: ";
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
        // ���ô���Ⱥ���߼�
        break;
    case 2:
        // ���ý�ɢȺ���߼�
        break;
    case 3:
        // ������ʾ����Ⱥ���߼�
        break;
    case 0:
        return;
    default:
        cout << "��Чѡ������ԡ�" << endl;
        break;
    }
}
