#include <Python.h>

int main(int argc, char *argv[])
{
	if(argc != 1) {
		fprintf(stderr, "Usage : %s\n", argv[0]);
		exit(1);
	}
    wchar_t *program = Py_DecodeLocale(argv[0], NULL);
    if (program == NULL) {
        fprintf(stderr, "Fatal error: cannot decode argv[0]\n");
        exit(1);
    }
    Py_SetProgramName(program);  /* optional but recommended */
    Py_Initialize();
    FILE* file = fopen("test.py", "r");;
    PyRun_SimpleFile(file, "atest.py");
    Py_Finalize();
    PyMem_RawFree(program);
    return 0;
}
