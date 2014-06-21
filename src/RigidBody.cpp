#include "pybulletphysics.h"

static void
RigidBody_dealloc(bulletphysics_RigidBodyObject* self)
{
        delete(self->rigidBody);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
RigidBody_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_rigidbodyCI = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_rigidbodyCI)) {
        	return NULL;
    	}

        bulletphysics_RigidBodyObject *self = (bulletphysics_RigidBodyObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_RigidBodyConstructionInfoObject *rigidbodyCI = (bulletphysics_RigidBodyConstructionInfoObject *) py_rigidbodyCI;
                self->rigidBody = new btRigidBody(*(rigidbodyCI->constructionInfo));
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_RigidBodyType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.RigidBody", /*tp_name*/
    sizeof(bulletphysics_RigidBodyObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)RigidBody_dealloc,    /*tp_dealloc*/
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
    "RigidBody object",           /* tp_doc */
};

void pybulletphysics_add_RigidBody(PyObject *module) {
	bulletphysics_RigidBodyType.tp_new = RigidBody_new;

        if (PyType_Ready(&bulletphysics_RigidBodyType) < 0)
                return;	

	Py_INCREF(&bulletphysics_RigidBodyType);

        PyModule_AddObject(module, "RigidBody", (PyObject *)&bulletphysics_RigidBodyType);
}
