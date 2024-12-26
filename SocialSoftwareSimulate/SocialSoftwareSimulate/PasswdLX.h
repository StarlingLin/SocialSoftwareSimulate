#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class PasswdLX
{
private:
    unordered_map<string, string> userPasswords; // �û��� -> ����ӳ��

    // �򵥼���
    string encryptPassword(const string& password) const;

public:
    PasswdLX();

    // �����û�����
    void setPassword(const string& username, const string& password);

    // ��֤�û�����
    bool validatePassword(const string& username, const string& password) const;

    // ����û����Ƿ����
    bool userExists(const string& username) const;
};