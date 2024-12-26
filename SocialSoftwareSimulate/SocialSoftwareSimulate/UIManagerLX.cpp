#include "UIManagerLX.h"
#include "PasswdLX.h"

UIManagerLX::UIManagerLX(LoggerLX* logger, UserManagerLX* userManager, ServiceManagerLX* serviceManager, GroupManagerLX* groupManager, DatabaseLX* database)
    : logger(logger), userManager(userManager), serviceManager(serviceManager), groupManager(groupManager), database(database), currentService(""), loggedInUser("") {
}

void UIManagerLX::start()
{
    // ���ط�������
    database->loadServices(serviceManager);
    database->loadGroups(groupManager);
    database->loadUsers(*userManager);

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

        // �����û���Ϣ�������ļ�
        database->saveUsers(*userManager);

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
    cout << "2. �û�����" << endl;
    cout << "3. Ⱥ�����" << endl;
    cout << "4. ���ط���ѡ��" << endl;
    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
		pageStack.push("User Info");
        displayUserInfo();
        break;
    case 2:
        pageStack.push("User Management");
        displayUserManagementMenu();
        break;
    case 3:
        pageStack.push("Group Management");
        displayGroupManagementMenu();
        break;
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}

void UIManagerLX::displayUserInfo()
{
    system("cls");
    cout << "�û�������Ϣ��" << endl;
    UserLX* user = userManager->getUser(loggedInUser);
    if (user)
    {
        cout << "�û�ID: " << user->getQQID() << endl;
        cout << "�ǳ�: " << user->getNickname() << endl;
        cout << "����ʱ��: " << user->getBirthDate() << endl;
        cout << "��������ʱ��: " << user->getTAge() << endl;
        cout << "���ڵ�: " << user->getLocation() << endl;
    }
    else
    {
        cout << "δ�ҵ��û���Ϣ��" << endl;
    }

    cout << "\n1. ����" << endl;
    cout << "2. �޸���Ϣ" << endl;
    int choice;
    cin >> choice;
    switch (choice)
    {
    case 1:
        pageStack.pop();
        break;
    case 2:
        modifyUserInfo();
        break;
    default:
        cout << "��Чѡ������ԡ�" << endl;
        break;
    }
}

void UIManagerLX::modifyUserInfo()
{
    system("cls");
    cout << "�޸��û���Ϣ��" << endl;
    cout << "�������µ��ǳƣ�";
    string newNickname;
    cin >> newNickname;
    cout << "�������µ����ڵأ�";
    string newLocation;
    cin >> newLocation;
	cout << "�������µĳ���ʱ�䣺";
	string newBirthDate;
	cin >> newBirthDate;
    UserLX* user = userManager->getUser(loggedInUser);
	cout << "�������µĺ�������ʱ�䣺";
	string newTAge;
	cin >> newTAge;
    if (user)
    {
        user->setNickname(newNickname);
        user->setLocation(newLocation);
		user->setBirthDate(newBirthDate);
		user->setTAge(newTAge);
        cout << "��Ϣ�޸ĳɹ���" << endl;
        logger->log("�û��޸��˸�����Ϣ��");
		database->saveUsers(*userManager);
    }
    else
    {
        cout << "δ�ҵ��û���Ϣ��" << endl;
    }

	system("pause");
	pageStack.pop();
}

void UIManagerLX::displayUserManagementMenu()
{
    system("cls");
    cout << "�û�����˵�" << endl;
    cout << "1. ��Ӻ���" << endl;
    cout << "2. ɾ������" << endl;
    cout << "3. �鿴�����б�" << endl;
    cout << "4. ����" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "���������ID: ";
        string friendID;
        cin >> friendID;
        friendManager.addFriend(currentService, loggedInUser, friendID);
        cout << "������ӳɹ���" << endl;
        break;
    }
    case 2:
    {
        cout << "������Ҫɾ���ĺ���ID: ";
        string friendID;
        cin >> friendID;
        friendManager.removeFriend(currentService, loggedInUser, friendID);
        cout << "����ɾ���ɹ���" << endl;
        break;
    }
    case 3:
    {
        cout << "�����б�" << endl;
        auto friends = friendManager.getFriends(currentService, loggedInUser);
        for (const auto& friendID : friends)
        {
            cout << friendID << endl;
        }
        break;
    }
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}

void UIManagerLX::displayGroupManagementMenu()
{
    system("cls");
    cout << "Ⱥ�����˵�" << endl;
    cout << "1. �鿴Ⱥ��" << endl;
    cout << "2. ����Ⱥ��" << endl;
    cout << "3. �˳�Ⱥ��" << endl;
    cout << "4. ����" << endl;

    int choice;
    cin >> choice;

    switch (choice)
    {
    case 1:
    {
        cout << "���Ѽ����Ⱥ�飺" << endl;
        if (groupManager)
        {
            auto groups = groupManager->getGroups(loggedInUser);
            for (const auto& groupID : groups)
            {
                cout << "Ⱥ��ID: " << groupID << endl;
            }
        }
        else
        {
            cout << "�޷���ȡȺ����Ϣ��" << endl;
        }
        break;
    }
    case 2:
    {
        cout << "������Ҫ�����Ⱥ��ID: ";
        int groupID;
        cin >> groupID;
        if (groupManager)
        {
            groupManager->joinGroup(groupID, loggedInUser);
            cout << "����Ⱥ��ɹ���" << endl;
        }
        else
        {
            cout << "�޷�����Ⱥ�飡" << endl;
        }
        break;
    }
    case 3:
    {
        cout << "������Ҫ�˳���Ⱥ��ID: ";
        int groupID;
        cin >> groupID;
        if (groupManager)
        {
            groupManager->leaveGroup(groupID, loggedInUser);
            cout << "�˳�Ⱥ��ɹ���" << endl;
        }
        else
        {
            cout << "�޷��˳�Ⱥ�飡" << endl;
        }
        break;
    }
    case 4:
        pageStack.pop();
        break;
    default:
        cout << "��Чѡ�������ѡ��" << endl;
        break;
    }
}
