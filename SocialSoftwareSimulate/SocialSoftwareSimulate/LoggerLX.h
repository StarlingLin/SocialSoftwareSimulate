#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class LoggerLX
{
private:
    string logFileName;            // ��־�ļ���
    vector<string> logBuffer;      // ��־����

    // ��ȡ��ǰʱ���ַ���
    string getCurrentTime() const;

public:
    LoggerLX(const string& fileName = "log.txt");

    // ��¼��־
    void log(const string& message);

    // ������־���ļ�
    void saveToFile();

    // �����־�ļ�
    void clearLogFile();
};
