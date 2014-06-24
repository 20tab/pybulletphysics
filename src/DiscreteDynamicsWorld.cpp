#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_CollisionDispatcherType;
extern PyTypeObject bulletphysics_DbvtBroadphaseType;
extern PyTypeObject bulletphysics_SequentialImpulseConstraintSolverType;
extern PyTypeObject bulletphysics_DefaultCollisionConfigurationType;
extern PyTypeObject bulletphysics_Vector3Type;
extern PyTypeObject bulletphysics_RigidBodyType;

static void
DiscreteDynamicsWorld_dealloc(bulletphysics_DynamicsWorldObject* self)
{
	Py_DECREF(self->broadphase);
	Py_DECREF(self->dispatcher);
	Py_DECREF(self->collision_configuration);
	Py_DECREF(self->solver);
        delete(self->world);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DiscreteDynamicsWorld_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	bulletphysics_DispatcherObject *py_dispatcher = NULL;
	bulletphysics_BroadphaseInterfaceObject *py_broadphase = NULL;
	bulletphysics_ConstraintSolverObject *py_solver = NULL;
	bulletphysics_CollisionConfigurationObject *py_collisionConfiguration = NULL;

	if (!PyArg_ParseTuple(args, "OOOO", &py_dispatcher, &py_broadphase, &py_solver, &py_collisionConfiguration)) {
        	return NULL;
    	}

	if (!PyObject_TypeCheck(py_dispatcher, &bulletphysics_CollisionDispatcherType)) {
		PyErr_SetString(PyExc_TypeError, "expected a CollisionDispatcherType");
		return NULL;
	}

	if (!PyObject_TypeCheck(py_broadphase, &bulletphysics_DbvtBroadphaseType)) {
		PyErr_SetString(PyExc_TypeError, "expected a DbvtBroadphaseType");
		return NULL;
	}

	if (!PyObject_TypeCheck(py_solver, &bulletphysics_SequentialImpulseConstraintSolverType)) {
		PyErr_SetString(PyExc_TypeError, "expected a SequentialImpulseConstraintSolverType");
		return NULL;
	}

	if (!PyObject_TypeCheck(py_collisionConfiguration, &bulletphysics_DefaultCollisionConfigurationType)) {
		PyErr_SetString(PyExc_TypeError, "expected a DefaultCollisionConfigurationType");
		return NULL;
	}

        bulletphysics_DynamicsWorldObject *self = (bulletphysics_DynamicsWorldObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->world = new btDiscreteDynamicsWorld(py_dispatcher->dispatcher, py_broadphase->broadphase, py_solver->solver, py_collisionConfiguration->configuration);
		self->broadphase = py_broadphase; Py_INCREF(self->broadphase);
		self->dispatcher = py_dispatcher; Py_INCREF(self->dispatcher);
		self->collision_configuration = py_collisionConfiguration; Py_INCREF(self->collision_configuration);
		self->solver = py_solver; Py_INCREF(self->solver);
        }
        return (PyObject *)self;
}

static PyObject *
DiscreteDynamicsWorld_setGravity(bulletphysics_DynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
	PyObject *py_vector3 = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
                return NULL;
        }

	if (!PyObject_TypeCheck(py_vector3, &bulletphysics_Vector3Type)) {
                PyErr_SetString(PyExc_TypeError, "expected a Vector3Type");
                return NULL;
        }

	bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
	self->world->setGravity(*(vector3->vector));

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
DiscreteDynamicsWorld_addRigidBody(bulletphysics_DynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
	PyObject *py_rigidBody = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_rigidBody)) {
                return NULL;
        }

	if (!PyObject_TypeCheck(py_rigidBody, &bulletphysics_RigidBodyType)) {
                PyErr_SetString(PyExc_TypeError, "expected a RigidBodyType");
                return NULL;
        }

	bulletphysics_RigidBodyObject *rigidBody = (bulletphysics_RigidBodyObject *) py_rigidBody;
	self->world->addRigidBody(rigidBody->rigidBody);

	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
DiscreteDynamicsWorld_stepSimulation(bulletphysics_DynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
	float ts = 0.0;
	float substeps = 1;
        if (!PyArg_ParseTuple(args, "f|f", &ts, &substeps)) {
                return NULL;
        }

        int ret = self->world->stepSimulation(ts, substeps);

        return PyInt_FromLong(ret);
}

static PyObject *
DiscreteDynamicsWorld_removeRigidBody(bulletphysics_DynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
        PyObject *py_rigidBody = NULL;
        if (!PyArg_ParseTuple(args, "O", &py_rigidBody)) {
                return NULL;
        }

	if (!PyObject_TypeCheck(py_rigidBody, &bulletphysics_RigidBodyType)) {
                PyErr_SetString(PyExc_TypeError, "expected a RigidBodyType");
                return NULL;
        }

        bulletphysics_RigidBodyObject *rigidBody = (bulletphysics_RigidBodyObject *) py_rigidBody;
        self->world->removeRigidBody(rigidBody->rigidBody);

        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *
DiscreteDynamicsWorld_getDispatcher(bulletphysics_DynamicsWorldObject *self, PyObject *args, PyObject *kwds) {
        return (PyObject *) self->dispatcher;
}

static PyMethodDef DiscreteDynamicsWorld_methods[] = {
    {"setGravity", (PyCFunction)DiscreteDynamicsWorld_setGravity, METH_VARARGS, NULL },
    {"addRigidBody", (PyCFunction)DiscreteDynamicsWorld_addRigidBody, METH_VARARGS, NULL },
    {"removeRigidBody", (PyCFunction)DiscreteDynamicsWorld_removeRigidBody, METH_VARARGS, NULL },
    {"stepSimulation", (PyCFunction)DiscreteDynamicsWorld_stepSimulation, METH_VARARGS, NULL },
    {"getDispatcher", (PyCFunction)DiscreteDynamicsWorld_getDispatcher, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};


static PyTypeObject bulletphysics_DiscreteDynamicsWorldType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DiscreteDynamicsWorld", /*tp_name*/
    sizeof(bulletphysics_DynamicsWorldObject), /*tp_basicsize*/
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
