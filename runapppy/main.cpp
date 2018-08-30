#include <Python.h>
//#include <string> 

int main(int argc, char *argv[])
{
	char program[_MAX_PATH];
	_fullpath(program, argv[0], _MAX_PATH);

	// get app dir
	//std::string fullpath = program;
	//size_t last = fullpath.find_last_of('\\');
	//std::string appdir = fullpath.substr(0, last);
	//printf("appdir=%s\n", appdir.c_str());

	Py_SetProgramName((wchar_t*)program);
	Py_Initialize();
	char cmd[_MAX_PATH];
	snprintf(cmd, sizeof(cmd), "import app; app.run()\n");

	//snprintf(cmd, sizeof(cmd),
	//	"import sys\n"
	//	"sys.path.append(r'%s\\..\\app')\n"
	//	"import app\n"
	//	"app.run()\n",
	//	appdir.c_str());

	PyRun_SimpleString(cmd);

	if (Py_FinalizeEx() < 0)
		exit(120);
	return 0;
}