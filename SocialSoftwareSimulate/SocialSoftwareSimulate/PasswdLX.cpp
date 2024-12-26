#include "PasswdLX.h"
#include <fstream>
#include <iostream>

using namespace std;

PasswdLX::PasswdLX()
{
    ifstream inFile("passwd.txt");
    if (inFile)
    {
        string username, password;
        while (inFile >> username >> password)
        {
            userPasswords[username] = password;
        }
        inFile.close();
    }
    else
    {
        cout << "未找到密码文件，将创建新文件。" << endl;
    }
}

string PasswdLX::encryptPassword(const string& password) const
{
    string encrypted = password;
    for (char& c : encrypted)
    {
        c = c + 3;
    }
    return encrypted;
}

void PasswdLX::setPassword(const string& username, const string& password)
{
    userPasswords[username] = encryptPassword(password);
    ofstream outFile("passwd.txt", ios::trunc);
    if (!outFile)
    {
        cerr << "无法打开密码文件进行保存。" << endl;
        return;
    }

    for (const auto& entry : userPasswords)
    {
        outFile << entry.first << " " << entry.second << endl;
    }

    outFile.close();
}

bool PasswdLX::validatePassword(const string& username, const string& password) const
{
    auto it = userPasswords.find(username);
    if (it != userPasswords.end())
    {
        return it->second == encryptPassword(password);
    }
    return false;
}

bool PasswdLX::userExists(const string& username) const
{
    return userPasswords.find(username) != userPasswords.end();
}
