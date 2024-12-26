#pragma once

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;

class LoggerLX
{
private:
    string logFileName;            // 日志文件名
    vector<string> logBuffer;      // 日志缓存

    // 获取当前时间字符串
    string getCurrentTime() const;

public:
    LoggerLX(const string& fileName = "log.txt");

    // 记录日志
    void log(const string& message);

    // 保存日志到文件
    void saveToFile();

    // 清空日志文件
    void clearLogFile();
};
