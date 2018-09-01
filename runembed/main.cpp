#include <Python.h>

// runapppy with implicit dll loading
// it needs python37.dll in same directory or PATH env var
// it also needs the app directory in PATH or in python37._pth
int main(int argc, char *argv[])
{
	char program[_MAX_PATH];
	_fullpath(program, argv[0], _MAX_PATH);
	Py_SetProgramName((wchar_t*)program);
	Py_Initialize();
	char cmd[_MAX_PATH];
	snprintf(cmd, sizeof(cmd), "import app; app.run()\n");
	PyRun_SimpleString(cmd);
	if (Py_FinalizeEx() < 0)
		exit(120);
	return 0;
}