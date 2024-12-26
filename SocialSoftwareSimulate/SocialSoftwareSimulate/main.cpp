#include "ManagerLX.h"
#include "UIManagerLX.h"
#include "LoggerLX.h"
#include "ServiceLX.h"

int main() {
    // ��ʼ����־������
    LoggerLX logger;

    // ��ʼ���û�������
    UserManagerLX userManager;

    // ��ʼ�����������
    ServiceManagerLX serviceManager;

    // ��ʼ��Ⱥ�������
    GroupManagerLX groupManager;

    // ��ʼ�����ݿ������
    DatabaseLX database;

    // ��ӷ���
    serviceManager.addService("QQ", new QQServiceLX());         // QQ ����
    serviceManager.addService("WeChat", new WXServiceLX());     // ΢�ŷ���
    serviceManager.addService("MicroA", new QQServiceLX());     // ΢A����ʹ��QQ�����߼���
    serviceManager.addService("MicroB", new WXServiceLX());     // ΢B����ʹ��΢�ŷ����߼���

    // ��ʼ�� UI ������
    UIManagerLX uiManager(&logger, &userManager, &serviceManager, &groupManager, &database);


    // ����ϵͳ
    uiManager.start();

    return 0;
}
