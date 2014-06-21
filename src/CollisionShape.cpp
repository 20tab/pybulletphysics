#include "pybulletphysics.h"

static void
CollisionShape_dealloc(bulletphysics_CollisionShapeObject* self)
{
        delete(self->shape);
        self->ob_type->tp_free((PyObject*)self);
}

PyTypeObject bulletphysics_CollisionShapeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.CollisionShape", /*tp_name*/
    sizeof(bulletphysics_CollisionShapeObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CollisionShape_dealloc,    /*tp_dealloc*/
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
    "CollisionShape object",           /* tp_doc */
};

static PyObject *
CollisionShape_calculateLocalInertia(bulletphysics_CollisionShapeObject *self, PyObject *args, PyObject *kwds) {
	float mass = 0.0;
        PyObject *py_vector3 = NULL;
        if (!PyArg_ParseTuple(args, "fO", &mass, &py_vector3)) {
                return NULL;
        }

        bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
        self->shape->calculateLocalInertia(mass, *(vector3->vector));

        Py_INCREF(Py_None);
        return Py_None;
}

static PyMethodDef CollisionShape_methods[] = {
    {"calculateLocalInertia", (PyCFunction)CollisionShape_calculateLocalInertia, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_CollisionShape(PyObject *module) {

	bulletphysics_CollisionShapeType.tp_methods = CollisionShape_methods;

        if (PyType_Ready(&bulletphysics_CollisionShapeType) < 0)
                return;	

	Py_INCREF(&bulletphysics_CollisionShapeType);

        PyModule_AddObject(module, "CollisionShape", (PyObject *)&bulletphysics_CollisionShapeType);
}
