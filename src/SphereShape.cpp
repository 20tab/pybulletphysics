#include "pybulletphysics.h"

static void
SphereShape_dealloc(bulletphysics_CollisionShapeObject* self)
{
        delete(self->shape);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
SphereShape_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float radius = 0;
	if (!PyArg_ParseTuple(args, "f", &radius)) {
        	return NULL;
    	}

        bulletphysics_CollisionShapeObject *self = (bulletphysics_CollisionShapeObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->shape = new btSphereShape(radius);
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_SphereShapeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.SphereShape", /*tp_name*/
    sizeof(bulletphysics_CollisionShapeObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)SphereShape_dealloc,    /*tp_dealloc*/
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
    "SphereShape object",           /* tp_doc */
};

void pybulletphysics_add_SphereShape(PyObject *module) {
	bulletphysics_SphereShapeType.tp_new = SphereShape_new;

        if (PyType_Ready(&bulletphysics_SphereShapeType) < 0)
                return;	

	Py_INCREF(&bulletphysics_SphereShapeType);

        PyModule_AddObject(module, "SphereShape", (PyObject *)&bulletphysics_SphereShapeType);
}
