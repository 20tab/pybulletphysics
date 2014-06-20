#include "pybulletphysics.h"

typedef struct {
        PyObject_HEAD
        btBroadphaseInterface *broadphase;
} bulletphysics_DbvtBroadphaseObject;

static void
DbvtBroadphase_dealloc(bulletphysics_DbvtBroadphaseObject* self)
{
        delete(self->broadphase);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DbvtBroadphase_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_DbvtBroadphaseObject *self = (bulletphysics_DbvtBroadphaseObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->broadphase = new btDbvtBroadphase();
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_DbvtBroadphaseType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DbvtBroadphase", /*tp_name*/
    sizeof(bulletphysics_DbvtBroadphaseObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)DbvtBroadphase_dealloc,    /*tp_dealloc*/
    0,                         /*tp_print*/
    0,                         /*tp_getattr*/
    0,                         /*tp_setattr*/
    0,                         /*tp_compare*/
    0,                         /*tp_repr*/
    0,                         /*tp_as_number*/
    0,                         /*tp_as_sequence*/
    0,                         /*tp_as_mapping*/
    0,                         /*tp_hash */
    0,                         /*tp_call*/
    0,                         /*tp_str*/
    0,                         /*tp_getattro*/
    0,                         /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "DbvtBroadphase object",           /* tp_doc */
};

void pybulletphysics_add_DbvtBroadphase(PyObject *module) {
	bulletphysics_DbvtBroadphaseType.tp_new = DbvtBroadphase_new;

        if (PyType_Ready(&bulletphysics_DbvtBroadphaseType) < 0)
                return;	

	Py_INCREF(&bulletphysics_DbvtBroadphaseType);

        PyModule_AddObject(module, "DbvtBroadphase", (PyObject *)&bulletphysics_DbvtBroadphaseType);
}
