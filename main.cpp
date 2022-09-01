#include "log.h"

int main() {
	Logger& log = Logger::GetInstance();
	log.Init(Logger::file_and_terminal, Logger::debug, "./log.txt");

	//auto f = [&]() { 
	//	if (log.GetTarget() == 0) return "file";
	//	else if (log.GetTarget() == 1) return "terminal";
	//	else return "termnal_and_file";};

	cout << "当前输出目标为：" <<
		[&]() {
		if (log.GetTarget() == 0) return "file";
		else if (log.GetTarget() == 1) return "terminal";
		else return "termnal_and_file"; }()
			<< endl;

	cout << "当前level为：" << log.GetLevel() << endl;

	log.Debug("There is a bug.");
	log.Info("Please read this information.");
	log.Warning("Be attention.");
	log.Error("ERROR！");

	system("pause");
	return 0;
}