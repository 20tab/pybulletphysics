#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_DefaultCollisionConfigurationType;

static void
CollisionDispatcher_dealloc(bulletphysics_DispatcherObject* self)
{
	Py_DECREF(self->collision_configuration);
        delete(self->dispatcher);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
CollisionDispatcher_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	bulletphysics_CollisionConfigurationObject *py_collisionConfiguration = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_collisionConfiguration)) {
        	return NULL;
    	}

	if (!PyObject_TypeCheck(py_collisionConfiguration, &bulletphysics_DefaultCollisionConfigurationType)) {
                PyErr_SetString(PyExc_TypeError, "expected a DefaultCollisionConfigurationType");
                return NULL;
        }

        bulletphysics_DispatcherObject *self = (bulletphysics_DispatcherObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->dispatcher = new btCollisionDispatcher(py_collisionConfiguration->configuration);
		self->collision_configuration = py_collisionConfiguration; Py_INCREF(self->collision_configuration);
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_CollisionDispatcherType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.CollisionDispatcher", /*tp_name*/
    sizeof(bulletphysics_DispatcherObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)CollisionDispatcher_dealloc,    /*tp_dealloc*/
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
    "CollisionDispatcher object",           /* tp_doc */
};

static PyObject *
CollisionDispatcher_getNumManifolds(bulletphysics_DispatcherObject *self, PyObject *args, PyObject *kwds) {
	return PyInt_FromLong(self->dispatcher->getNumManifolds());
}

static PyMethodDef CollisionDispatcher_methods[] = {
    {"getNumManifolds", (PyCFunction)CollisionDispatcher_getNumManifolds, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_CollisionDispatcher(PyObject *module) {
	bulletphysics_CollisionDispatcherType.tp_methods = CollisionDispatcher_methods;
	bulletphysics_CollisionDispatcherType.tp_new = CollisionDispatcher_new;

        if (PyType_Ready(&bulletphysics_CollisionDispatcherType) < 0)
                return;	

	Py_INCREF(&bulletphysics_CollisionDispatcherType);

        PyModule_AddObject(module, "CollisionDispatcher", (PyObject *)&bulletphysics_CollisionDispatcherType);
}
