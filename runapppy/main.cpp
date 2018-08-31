#ifdef _DEBUG
#undef _DEBUG
#include <Python.h>
#define _DEBUG
#else
#include <Python.h>
#endif

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