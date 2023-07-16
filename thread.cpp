#ifdef _DEBUG
#undef _DEBUG

#include <Python.h>

#define _DEBUG
#else
#include <Python.h>
#endif

#include <thread>

#ifdef _MSC_VER
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif

#ifdef __cplusplus
extern "C"
{
#endif

    static std::thread *thread = nullptr;
    DLL_EXPORT PyObject *py_join_thread(PyObject *, PyObject *);
    DLL_EXPORT PyObject *py_new_thread(PyObject *self, PyObject *args)
    {
        if (thread)
        {
            py_join_thread(nullptr, nullptr);
        }
        // assume only one argument
        auto *pyFunction = PyTuple_GetItem(args, 0);

        thread = new std::thread([pyFunction]()
                                 {
        PyGILState_STATE gstate;
        gstate = PyGILState_Ensure(); // The Python interpreter is not thread-safe by default
        PyObject_CallObject(pyFunction, NULL);
        PyGILState_Release(gstate); });

        Py_RETURN_NONE;
    }

    DLL_EXPORT PyObject *py_join_thread(PyObject *self, PyObject *args)
    {
        if (thread)
        {
            thread->join();
        }
        delete thread;
        thread = nullptr;

        Py_RETURN_NONE;
    }

    static PyMethodDef methods[] = {
        {"join_thread", py_join_thread, METH_NOARGS},
        {"new_thread", py_new_thread, METH_VARARGS},
        {NULL, NULL}};

    DLL_EXPORT void initmy_python_lib(void)
    {
        // Init module.
        (void)Py_InitModule("my_python_lib", methods);
    }

#ifdef __cplusplus
}
#endif
