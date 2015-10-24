/*
The MIT License (MIT)

Copyright (c) 2015 Rakholiya Jenish

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#include <Python.h>
#include <cxxabi.h>

static PyObject *demangle (PyObject *self, PyObject *args) {
    const char *mangled_name;
    char *demangled_name;
    int status = -1;
    if (!PyArg_ParseTuple(args, "s", &mangled_name))
        return NULL;
    demangled_name = abi::__cxa_demangle(mangled_name,NULL,NULL,&status);
    if ( status == 0 )
        return Py_BuildValue("s",demangled_name);
    else
        return NULL;
}

static PyMethodDef DemangleMethods[] = {
    {"demangle", demangle, METH_VARARGS, "Demangle the C++ Mangled Name"}
};

PyMODINIT_FUNC initdemangle(void){
    (void) Py_InitModule("demangle", DemangleMethods);
}

int main (int argc, char **argv) {
    Py_SetProgramName(argv[0]);
    Py_Initialize();
    initdemangle();
    return 0;
}
