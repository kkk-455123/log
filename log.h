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
	enum logLevel { debug, info, warning, error };  // ��־�ȼ�
	enum logTarget { file, terminal, file_and_terminal };  // ��־���Ŀ��

public:
	// ��ȡ����
	static Logger& GetInstance();

	// ��ʼ��
	void Init(logTarget, logLevel, string);

	// ����/��ȡ��־�ȼ������Ŀ��
	logLevel GetLevel() const;
	logTarget GetTarget() const;
	void SetLevel(logLevel level);
	void SetTarget(logTarget target);

	// �ĸ��ӿ�
	void Debug(string text);
	void Info(string text);
	void Warning(string text);
	void Error(string text);

private:
	// ���캯��˽�л�
	Logger();
	Logger(const Logger&);
	Logger& operator=(const Logger&);
	~Logger();

	// ��ȡ��ǰʱ��
	string CurrTime();

	// д��־����
	void logWrite(string, logLevel);

private:
	ofstream outfile;  // ����־������ļ����ļ�������
	string filePath;  // �ļ�·��
	logLevel m_level;
	logTarget m_target;

	mutable mutex mtx;
};