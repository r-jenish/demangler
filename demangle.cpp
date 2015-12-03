#include <Python.h>
#include <cxxabi.h>

#if PY_MAJOR_VERSION >= 3
#if PY_MINOR_VERSION < 5
static wchar_t* Py_DecodeLocale(const char* arg, size_t*) {
    size_t argsize = mbstowcs(NULL, arg, 0);
    if (argsize == (size_t)-1) {
        return NULL;
    }
    if (argsize == PY_SSIZE_T_MAX) {
        return NULL;
    }
    if (argsize > PY_SSIZE_T_MAX/sizeof(wchar_t)) {
        return NULL;
    }
    wchar_t *res = (wchar_t *)PyMem_RawMalloc(argsize*sizeof(wchar_t));
    if (!res) {
        return NULL;
    }
    size_t count = mbstowcs(res, arg, argsize);
    if (count != (size_t)-1) {
        wchar_t *tmp;
        for (tmp = res; *tmp != 0 && !Py_UNICODE_IS_SURROGATE(*tmp); tmp++) {
        }
        if (*tmp == 0) {
            return res;
        }
    }
    PyMem_RawFree(res);
    return NULL;
}
#endif
    #define MOD_SUCCESS_VALUE(value) (value)
    #define MOD_INIT(name) PyInit_##name
    #define MOD_DEF(ob, name, methods) \
        do { \
            static struct PyModuleDef moduledef = { \
                PyModuleDef_HEAD_INIT, #name, NULL, -1, methods \
            }; \
            ob = PyModule_Create(&moduledef); \
        } while (0)
    #define MOD_SET_PROGRAM_NAME(name) \
        do { \
            wchar_t* buf = Py_DecodeLocale(name, NULL); \
            if (buf) {Py_SetProgramName(buf);PyMem_RawFree(buf);} \
        } while (0)
#elif PY_MAJOR_VERSION == 2
    #define MOD_SUCCESS_VALUE(value)
    #define MOD_INIT(name) init##name
    #define MOD_DEF(ob, name, methods) \
        do { \
            ob = Py_InitModule(#name, methods); \
        } while (0)
    #define MOD_SET_PROGRAM_NAME(name) \
        Py_SetProgramName(name)
#else
    #error "Unsupported Python Version!"
#endif

static PyObject *demangle (PyObject *self, PyObject *args) {
    const char *mangled_name;
    char *demangled_name;
    int status = -1;
    if (!PyArg_ParseTuple(args, "s", &mangled_name))
        return NULL;
    demangled_name = abi::__cxa_demangle(mangled_name, NULL, NULL, &status);
    PyObject * po = status == 0 ? Py_BuildValue("s",demangled_name) : Py_BuildValue("s",mangled_name);
    free(demangled_name);
    return po;
}

PyMODINIT_FUNC MOD_INIT(_demangler)(void) {
    static PyMethodDef DemangleMethods[] = {
        {"demangle", demangle, METH_VARARGS, "Demangle the c++ Mangled Name"},
        {NULL, NULL, 0, NULL}
    };
    PyObject *m;
    MOD_DEF(m, _demangler, DemangleMethods);
    return MOD_SUCCESS_VALUE(m);
}

int main (int argc, char **argv) {
    MOD_SET_PROGRAM_NAME(argv[0]);
    Py_Initialize();
    MOD_INIT(_demangler)();
    return 0;
}
