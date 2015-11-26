#include <Python.h>
#include <cxxabi.h>

static PyObject *demangle (PyObject *self, PyObject *args) {
    const char *mangled_name;
    char *demangled_name;
    int status = -1;
    if (!PyArg_ParseTuple(args, "s", &mangled_name))
        return NULL;
    demangled_name = abi::__cxa_demangle(mangled_name,NULL,NULL,&status);
    PyObject * po = status == 0 ? Py_BuildValue("s",demangled_name) : Py_BuildValue("s",mangled_name);    
    free(demangled_name);
    return po;
}

static PyMethodDef DemangleMethods[] = {
    {"demangle", demangle, METH_VARARGS, "Demangle the c++ Mangled Name"}
};

PyMODINIT_FUNC initdemangler(void){
    (void) Py_InitModule("demangler", DemangleMethods);
}

int main (int argc, char **argv) {
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initdemangler();
    return 0;
}
