#include <stdio.h>
#include <stdlib.h> // _get_pgmptr
#include <string>

int main(int argc, char *argv[])
{
	char* program;
	_get_pgmptr(&program);
	char cmd[512];
	std::string fullpath = program;
	std::string directory;
	const size_t last_slash_idx = fullpath.rfind('\\');
	if (std::string::npos != last_slash_idx)
		directory = fullpath.substr(0, last_slash_idx);
	sprintf_s(cmd, "%s\\python\\runapppy.exe", directory.c_str());
	printf(cmd);
	system((char *)cmd);
}