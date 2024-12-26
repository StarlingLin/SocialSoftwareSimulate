#pragma once

#include <string>
#include <unordered_map>

using namespace std;

class PasswdLX
{
private:
    unordered_map<string, string> userPasswords; // 用户名 -> 密码映射

    // 简单加密
    string encryptPassword(const string& password) const;

public:
    PasswdLX();

    // 设置用户密码
    void setPassword(const string& username, const string& password);

    // 验证用户密码
    bool validatePassword(const string& username, const string& password) const;

    // 检查用户名是否存在
    bool userExists(const string& username) const;
};