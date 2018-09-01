#include <windows.h>	
#include <stdlib.h>		// sprintf_s
#include <stdarg.h>
#include <string>
#include <fstream>

// get executable full path
inline std::string get_exepath()
{
	char buffer[MAX_PATH];
	char exepath[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	_fullpath(exepath, buffer, MAX_PATH);
	return std::string (exepath);
}
// get time
inline std::string now() 
{
	SYSTEMTIME t;
	GetLocalTime(&t);
	std::string strMessage;
	char buffer[256];
	sprintf_s(buffer, "%d-%02d-%02d %02d:%02d:%02d", t.wYear, t.wMonth,
		t.wDay, t.wHour, t.wMinute,t.wSecond);
	return std::string(buffer);
}
void write_log(const char *fmt, ...)
{
	
}

// log text file with message
inline void log(std::string exepath, const char* msg, ...)
{
	char message[1000];
	va_list args;
	va_start(args, msg);
	vsprintf_s(message, msg, args);
	va_end(args);
	std::string path = exepath + ".log";
	std::ofstream ofs(path.c_str(), std::ios_base::out | std::ios_base::app);
	ofs << now() << ": " << std::string(message) << '\n';
	ofs.close();	
}
// read config.json and get "apppath" value
inline std::string get_apppath(const std::string& exepath)
{
	char confpath[MAX_PATH];
	std::string appdir = exepath.substr(0, exepath.find_last_of("\\/"));
	sprintf_s(confpath, "%s\\config.json", appdir.c_str());
	std::ifstream file(confpath);
	if (!file) {
		log(exepath, "Cannot open %s", confpath);
		exit(2);
	}
	std::string line = "";
	std::string apppath = "";
	while (std::getline(file, line, ':') && !file.eof())
	{
		if (line.find("\"apppath\"") != std::string::npos) {
			std::getline(file, apppath, '"');
			std::getline(file, apppath, '"');
		}
	}	
	file.close();
	if (apppath == "") {
		log(exepath, "Cannot read \"apppath\" key in %s", confpath);
		exit(3);
	}
	char fullapppath[MAX_PATH];
	sprintf_s(fullapppath, "%s\\%s", appdir.c_str(), apppath.c_str());
	return std::string(fullapppath);
}

// app without window
int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	std::string exepath = get_exepath();
	std::string apppath = get_apppath(exepath);
	int ret = (int)ShellExecute(0, "open", apppath.c_str(), "", 0, 1);
	if (ret <= 32)
		log(exepath, "Cannot run %s, error code: %d", apppath.c_str(), ret);
	return 0;
}