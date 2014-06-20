#include "pybulletphysics.h"

static void
CollisionDispatcher_dealloc(bulletphysics_CollisionDispatcherObject* self)
{
        delete(self->dispatcher);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
CollisionDispatcher_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_collisionConfiguration = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_collisionConfiguration)) {
        	return NULL;
    	}

        bulletphysics_CollisionDispatcherObject *self = (bulletphysics_CollisionDispatcherObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_DefaultCollisionConfigurationObject *collisionConfiguration = (bulletphysics_DefaultCollisionConfigurationObject *) py_collisionConfiguration;
                self->dispatcher = new btCollisionDispatcher(collisionConfiguration->configuration);
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_CollisionDispatcherType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.CollisionDispatcher", /*tp_name*/
    sizeof(bulletphysics_CollisionDispatcherObject), /*tp_basicsize*/
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

void pybulletphysics_add_CollisionDispatcher(PyObject *module) {
	bulletphysics_CollisionDispatcherType.tp_new = CollisionDispatcher_new;

        if (PyType_Ready(&bulletphysics_CollisionDispatcherType) < 0)
                return;	

	Py_INCREF(&bulletphysics_CollisionDispatcherType);

        PyModule_AddObject(module, "CollisionDispatcher", (PyObject *)&bulletphysics_CollisionDispatcherType);
}
