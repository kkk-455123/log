#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <mutex>

using namespace std;

class Logger
{
public:
	enum logLevel { debug, info, warning, error };  // 日志等级
	enum logTarget { file, terminal, file_and_terminal };  // 日志输出目标

public:
	// 获取单例
	static Logger& GetInstance();

	// 初始化
	void Init(logTarget, logLevel, string);

	// 设置/获取日志等级和输出目标
	logLevel GetLevel() const;
	logTarget GetTarget() const;
	void SetLevel(logLevel level);
	void SetTarget(logTarget target);

	// 四个接口
	void Debug(string text);
	void Info(string text);
	void Warning(string text);
	void Error(string text);

private:
	// 构造函数私有化
	Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	~Logger();

	// 获取当前时间
	string CurrTime();

	// 写日志操作
	void logWrite(string, logLevel);

private:
	ofstream outfile;  // 将日志输出到文件的文件流对象；
	string filePath;  // 文件路径
	logLevel m_level;
	logTarget m_target;

	mutable mutex mtx;
};