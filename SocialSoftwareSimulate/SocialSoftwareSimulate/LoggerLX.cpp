#pragma once
#include "LoggerLX.h"
#include <ctime>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

LoggerLX::LoggerLX(const string& fileName)
    : logFileName(fileName) {
}

string LoggerLX::getCurrentTime() const
{
    time_t now = time(0);
    tm* localtm = localtime(&now);
    char buffer[80];
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtm);
    return string(buffer);
}

void LoggerLX::log(const string& message)
{
    string timeStampedMessage = getCurrentTime() + " - " + message;
    logBuffer.push_back(timeStampedMessage);
    cout << timeStampedMessage << endl; // 打印到控制台
}

void LoggerLX::saveToFile()
{
    ofstream outFile(logFileName, ios::app);
    if (!outFile)
    {
        cerr << "无法打开日志文件: " << logFileName << endl;
        return;
    }

    for (const auto& logEntry : logBuffer)
    {
        outFile << logEntry << endl;
    }
    logBuffer.clear();
    outFile.close();
}

void LoggerLX::clearLogFile()
{
    ofstream outFile(logFileName, ios::trunc);
    if (!outFile)
    {
        cerr << "无法清空日志文件: " << logFileName << endl;
        return;
    }
    outFile.close();
    cout << "日志文件已清空: " << logFileName << endl;
}
