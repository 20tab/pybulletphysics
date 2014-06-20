#include "pybulletphysics.h"

static void
DiscreteDynamicsWorld_dealloc(bulletphysics_DiscreteDynamicsWorldObject* self)
{
        delete(self->world);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DiscreteDynamicsWorld_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_dispatcher = NULL;
	PyObject *py_broadphase = NULL;
	PyObject *py_solver = NULL;
	PyObject *py_collisionConfiguration = NULL;

	if (!PyArg_ParseTuple(args, "OOOO", &py_dispatcher, &py_broadphase, &py_solver, &py_collisionConfiguration)) {
        	return NULL;
    	}

        bulletphysics_DiscreteDynamicsWorldObject *self = (bulletphysics_DiscreteDynamicsWorldObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_CollisionDispatcherObject *dispatcher = (bulletphysics_CollisionDispatcherObject *) py_dispatcher;
		bulletphysics_DbvtBroadphaseObject *broadphase = (bulletphysics_DbvtBroadphaseObject *) py_broadphase;
		bulletphysics_SequentialImpulseConstraintSolverObject *solver = (bulletphysics_SequentialImpulseConstraintSolverObject *) py_solver;
		bulletphysics_DefaultCollisionConfigurationObject *collisionConfiguration = (bulletphysics_DefaultCollisionConfigurationObject *) py_collisionConfiguration;
                self->world = new btDiscreteDynamicsWorld(dispatcher->dispatcher, broadphase->broadphase, solver->solver, collisionConfiguration->configuration);
        }
        return (PyObject *)self;
}

static PyObject *
DiscreteDynamicsWorld_setGravity(bulletphysics_DiscreteDynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
	PyObject *py_vector3 = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
                return NULL;
        }

	bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
	self->world->setGravity(*(vector3->vector));

	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef DiscreteDynamicsWorld_methods[] = {
    {"setGravity", (PyCFunction)DiscreteDynamicsWorld_setGravity, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};


static PyTypeObject bulletphysics_DiscreteDynamicsWorldType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DiscreteDynamicsWorld", /*tp_name*/
    sizeof(bulletphysics_DiscreteDynamicsWorldObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)DiscreteDynamicsWorld_dealloc,    /*tp_dealloc*/
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
    "DiscreteDynamicsWorld object",           /* tp_doc */
};

void pybulletphysics_add_DiscreteDynamicsWorld(PyObject *module) {
	bulletphysics_DiscreteDynamicsWorldType.tp_new = DiscreteDynamicsWorld_new;
	bulletphysics_DiscreteDynamicsWorldType.tp_methods = DiscreteDynamicsWorld_methods;

        if (PyType_Ready(&bulletphysics_DiscreteDynamicsWorldType) < 0)
                return;	

	Py_INCREF(&bulletphysics_DiscreteDynamicsWorldType);

        PyModule_AddObject(module, "DiscreteDynamicsWorld", (PyObject *)&bulletphysics_DiscreteDynamicsWorldType);
}
