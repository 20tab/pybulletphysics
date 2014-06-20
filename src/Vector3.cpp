#include "pybulletphysics.h"

static void
Vector3_dealloc(bulletphysics_Vector3Object* self)
{
        delete(self->vector);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Vector3_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)) {
        	return NULL;
    	}

        bulletphysics_Vector3Object *self = (bulletphysics_Vector3Object *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->vector = new btVector3(x, y, z);
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_Vector3Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.Vector3", /*tp_name*/
    sizeof(bulletphysics_Vector3Object), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Vector3_dealloc,    /*tp_dealloc*/
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
    "Vector3 object",           /* tp_doc */
};

void pybulletphysics_add_Vector3(PyObject *module) {
	bulletphysics_Vector3Type.tp_new = Vector3_new;

        if (PyType_Ready(&bulletphysics_Vector3Type) < 0)
                return;	

	Py_INCREF(&bulletphysics_Vector3Type);

        PyModule_AddObject(module, "Vector3", (PyObject *)&bulletphysics_Vector3Type);
}
