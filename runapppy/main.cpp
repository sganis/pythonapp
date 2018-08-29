#include <Python.h>
#include <stdlib.h> // _get_pgmptr

int main(int argc, char *argv[])
{
	char* program;
	_get_pgmptr(&program);
	//printf(program);
	Py_SetProgramName((wchar_t*)program);
	Py_Initialize();
	char cmd[1000];
	snprintf(cmd, sizeof(cmd),
		"import sys; import os\n"
		"appdir=os.path.dirname(r'%s')\n"
		"apppath=os.path.realpath(appdir + r'\\..\\app')\n"
		"sys.path.append(apppath)\n"
		"import app\n"
		"app.run()\n",
		program);
	PyRun_SimpleString(cmd);

	if (Py_FinalizeEx() < 0)
		exit(120);
	return 0;
}