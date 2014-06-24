#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_RigidBodyType;

static void
PersistentManifold_dealloc(bulletphysics_PersistentManifoldObject* self)
{
	if (!self->do_not_delete) {
        	delete(self->manifold);
	}
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
PersistentManifold_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_PersistentManifoldObject *self = (bulletphysics_PersistentManifoldObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->manifold = new btPersistentManifold();
		self->do_not_delete = 0;
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_PersistentManifoldType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.PersistentManifold", /*tp_name*/
    sizeof(bulletphysics_PersistentManifoldObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)PersistentManifold_dealloc,    /*tp_dealloc*/
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
    "PersistentManifold object",           /* tp_doc */
};

PyObject *new_pypersistentmanifold_from_persistentmanifold(btPersistentManifold *manifold) {
        bulletphysics_PersistentManifoldObject *py_manifold = (bulletphysics_PersistentManifoldObject *)bulletphysics_PersistentManifoldType.tp_alloc(&bulletphysics_PersistentManifoldType, 0);
        if (py_manifold) {
                py_manifold->manifold = manifold;
		py_manifold->do_not_delete = 1;
                Py_INCREF(py_manifold);
        }
        return (PyObject *)py_manifold;
}

static PyObject *
PersistentManifold_getX(bulletphysics_PersistentManifoldObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(0);
}

static PyObject *
PersistentManifold_getY(bulletphysics_PersistentManifoldObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(0);
}

static PyMethodDef PersistentManifold_methods[] = {
    {"getBody0", (PyCFunction)PersistentManifold_getX, METH_VARARGS, NULL },
    {"getBody1", (PyCFunction)PersistentManifold_getY, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_PersistentManifold(PyObject *module) {
	bulletphysics_PersistentManifoldType.tp_methods = PersistentManifold_methods;
	bulletphysics_PersistentManifoldType.tp_new = PersistentManifold_new;

        if (PyType_Ready(&bulletphysics_PersistentManifoldType) < 0)
                return;	

	Py_INCREF(&bulletphysics_PersistentManifoldType);

        PyModule_AddObject(module, "PersistentManifold", (PyObject *)&bulletphysics_PersistentManifoldType);
}
