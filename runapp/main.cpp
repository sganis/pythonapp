#include <windows.h>	
#include <stdlib.h>		// sprintf_s
#include <string>
#include <fstream>

std::string read_config(const std::string& appdir)
{
	char confpath[MAX_PATH];
	sprintf_s(confpath, "%s\\config.json", appdir.c_str());
	std::ifstream file(confpath);
	std::string line;
	std::string exepath;
	while (std::getline(file, line, ':') && !file.eof())
	{
		if (line.find("\"runapp\"") != std::string::npos) {
			std::getline(file, exepath, '"');
			std::getline(file, exepath, '"');
		}
	}	
	file.close();
	char exe[MAX_PATH];
	sprintf_s(exe, "%s\\%s", appdir.c_str(), exepath.c_str());
	return std::string(exe);
}


int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int cmdShow)
{
	char buffer[MAX_PATH];
	char program[MAX_PATH];
	GetModuleFileName(NULL, buffer, MAX_PATH);
	_fullpath(program, buffer, MAX_PATH);
	std::string fullpath = program;
	std::string appdir = fullpath.substr(0, fullpath.find_last_of("\\/"));
	std::string exe = read_config(appdir);
	ShellExecute(0, "open", exe.c_str(), "", 0, 1);
	return 0;
}