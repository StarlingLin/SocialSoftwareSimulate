#include "CommunicationSystemLX.h"

using namespace std;

// 构造函数
CommunicationSystemLX::CommunicationSystemLX(GroupManagerLX* grpManager, ServiceManagerLX* srvManager)
    : groupManager(grpManager), serviceManager(srvManager)
{
}

// 系统初始化
void CommunicationSystemLX::initialize()
{
    cout << "正在初始化通信系统..." << endl;

    // 从数据库加载数据
    database.loadUsers(userManager);
    database.loadGroups(groupManager);
    database.loadServices(serviceManager);

    // 初始化日志
    logger.log("系统初始化成功。");

    cout << "初始化完成。" << endl;
}

// 系统运行主逻辑
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
            cout << "请输入用户ID: ";
            cin >> userID;
            cout << "请输入昵称: ";
            cin >> nickname;
            userManager.addUser(userID, nickname, "未知", "未知", "未知");
            logger.log("用户已添加: " + userID);
            break;
        }
        case 2:
        {
            string userID;
            cout << "请输入要移除的用户ID: ";
            cin >> userID;
            userManager.removeUser(userID);
            logger.log("用户已移除: " + userID);
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
            cout << "请输入服务名称: ";
            cin >> serviceName;
            ServiceLX* service = serviceManager->getService(serviceName);
            if (service)
            {
                service->displayServiceInfo();
            }
            else
            {
                cout << "未找到指定服务。" << endl;
            }
            break;
        }
        case 5:
        {
            string userID, friendID;
            cout << "请输入您的用户ID: ";
            cin >> userID;
            cout << "请输入要添加的好友用户ID: ";
            cin >> friendID;
            if (userManager.userExists(userID) && userManager.userExists(friendID))
            {
                ServiceLX* qqService = serviceManager->getService("QQ");
                if (qqService)
                {
                    qqService->addFriend(userID, friendID);
                    logger.log("好友已添加: " + friendID + " 给用户: " + userID);
                    cout << "好友添加成功！" << endl;
                }
            }
            else
            {
                cout << "用户ID无效。" << endl;
            }
            break;
        }
        case 6:
        {
            int groupID;
            string userID;
            cout << "请输入群组ID: ";
            cin >> groupID;
            cout << "请输入您的用户ID以加入群组: ";
            cin >> userID;
            if (userManager.userExists(userID))
            {
                groupManager->joinGroup(groupID, userID);
                logger.log("用户加入群组: " + to_string(groupID));
                cout << "成功加入群组！" << endl;
            }
            else
            {
                cout << "用户ID无效。" << endl;
            }
            break;
        }
        case 0:
            isRunning = false;
            break;
        default:
            cout << "无效选项，请重试。" << endl;
        }
    }

    cout << "正在退出系统..." << endl;
    logger.log("系统退出。");
}

// 系统退出
void CommunicationSystemLX::shutdown()
{
    cout << "正在保存数据并关闭系统..." << endl;

    // 将数据保存到数据库
    database.saveUsers(userManager);
    database.saveGroups(groupManager);
    database.saveServices(serviceManager);

    logger.log("系统关闭完成。");
}

// 主菜单
void CommunicationSystemLX::displayMenu() const
{
    cout << "\n===== 通信系统菜单 =====" << endl;
    cout << "1. 添加用户" << endl;
    cout << "2. 移除用户" << endl;
    cout << "3. 显示所有用户" << endl;
    cout << "4. 显示服务信息" << endl;
    cout << "5. 添加好友" << endl;
    cout << "6. 加入群组" << endl;
    cout << "0. 退出" << endl;
    cout << "======================" << endl;
    cout << "请输入选项: ";
}
