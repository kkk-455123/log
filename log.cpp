#include "log.h"

// 默认调试等级 控制台输出
Logger::Logger() : m_level(debug), m_target(terminal) {}

void
Logger::Init(logTarget target, logLevel level, string path) {
	m_level = level;
	m_target = target;
	string welcomeDialog = __FILE__ + string(" ") + CurrTime() + " : " + "Start Logging\n";
	if (target != file) { cout << welcomeDialog; }
	if (target != terminal) {
		if (!outfile.is_open()) {
			this->outfile.open(path, ios::out | ios::app);
		}
		outfile << welcomeDialog;
	}
}

Logger&
Logger::GetInstance() {
	static Logger instance;
	return instance;
}

Logger::logLevel 
Logger::GetLevel() const { 
	lock_guard<mutex> locker(mtx);
	return m_level; 
}

Logger::logTarget
Logger::GetTarget() const { 
	lock_guard<mutex> locker(mtx);
	return m_target; 
}

void 
Logger::SetLevel(logLevel level) { 
	lock_guard<mutex> locker(mtx);
	m_level = level; 
}

void
Logger::SetTarget(logTarget target) { 
	lock_guard<mutex> locker(mtx);
	m_target = target; 
}

string 
Logger::CurrTime() {
	char temp[30];
	time_t rawTime;  // 存放当前日历时间
	struct tm localTime;  // 存放转换后的本地时间

	time(&rawTime);  // 计算当前日历时间
	localtime_s(&localTime, &rawTime);  // 转换为本地时间

	strftime(temp, sizeof(temp), "%Y-%m-%d %H:%M:%S", &localTime);  
	return temp;
}

void
Logger::logWrite(string text, logLevel actLevel) {
	string pre;
	if (actLevel == debug) pre = "[DEBUG]";
	else if (actLevel == info) pre = "[INFO]";
	else if (actLevel == warning) pre = "[WARNING]";
	else if (actLevel == error) pre = "[ERROR]";
	else pre = "";

	string dialog = pre + " " + __FILE__ + " " + CurrTime() + " : " + text + "\n";

	// 当执行level大于等于设定level时才显示到终端
	if (actLevel >= this->m_level && this->m_target != file) {
		cout << dialog;
	}
	// 文件中记录所有level的信息
	if (m_target != terminal) {
		outfile << dialog;
	}
}

void
Logger::Debug(string text) {
	logWrite(text, debug);
}

void
Logger::Info(string text) {
	logWrite(text, info);
}

void 
Logger::Warning(string text) {
	logWrite(text, warning);
}

void
Logger::Error(string text) {
	logWrite(text, error);
}


Logger::~Logger() {
	if (outfile.is_open()) outfile.close();
}