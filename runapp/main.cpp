//#include <stdio.h>
//#include <windows.h>	// GetFullPathName
#include <stdlib.h>		// sprintf_s
#include <string>

int main(int argc, char *argv[])
{
	// get app dir
	char program[_MAX_PATH];
	char cmd[_MAX_PATH];

	_fullpath(program, argv[0], _MAX_PATH);
	std::string fullpath = program;
	std::string appdir = fullpath.substr(0, fullpath.length() - 4);

	//size_t last = fullpath.find_last_of('\\');
	//std::string appdir = fullpath.substr(0, last);
	//printf("appdir=%s\n", appdir.c_str());
	
	sprintf_s(cmd, "%s\\runapppy.exe", appdir.c_str());

	//sprintf_s(cmd, "%s\\app\\runmain.exe", appdir.c_str());
	//sprintf_s(cmd, "%s\\python\\python.exe %s\\app\\app.py", appdir.c_str(), appdir.c_str());
	//printf(cmd);
	system((char *)cmd);
}