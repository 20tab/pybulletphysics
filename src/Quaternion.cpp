#include "pybulletphysics.h"

static void
Quaternion_dealloc(bulletphysics_QuaternionObject* self)
{
        delete(self->quaternion);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Quaternion_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float w = 0.0;
	if (!PyArg_ParseTuple(args, "ffff", &x, &y, &z)) {
        	return NULL;
    	}

        bulletphysics_QuaternionObject *self = (bulletphysics_QuaternionObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->quaternion = new btQuaternion(x, y, z, w);
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_QuaternionType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.Quaternion", /*tp_name*/
    sizeof(bulletphysics_QuaternionObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Quaternion_dealloc,    /*tp_dealloc*/
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
    "Quaternion object",           /* tp_doc */
};

void pybulletphysics_add_Quaternion(PyObject *module) {
	bulletphysics_QuaternionType.tp_new = Quaternion_new;

        if (PyType_Ready(&bulletphysics_QuaternionType) < 0)
                return;	

	Py_INCREF(&bulletphysics_QuaternionType);

        PyModule_AddObject(module, "Quaternion", (PyObject *)&bulletphysics_QuaternionType);
}