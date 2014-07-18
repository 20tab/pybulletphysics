#include "pybulletphysics.h"
#include <stddef.h>

extern PyTypeObject bulletphysics_TransformType;

static void
RigidBody_dealloc(bulletphysics_RigidBodyObject* self)
{
	Py_XDECREF(self->dict);
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
        self->rigidBody->setUserPointer(self);
        self->dict = NULL;
    }
    return (PyObject *)self;
}

PyTypeObject bulletphysics_RigidBodyType = {
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
    PyObject_GenericGetAttr,   /*tp_getattro*/
    PyObject_GenericSetAttr,   /*tp_setattro*/
    0,                         /*tp_as_buffer*/
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE, /*tp_flags*/
    "RigidBody object",           /* tp_doc */
};

static PyObject *
RigidBody_applyCentralForce(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->applyCentralForce(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_applyForce(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    PyObject *py_vector3_pos = NULL;
    if (!PyArg_ParseTuple(args, "OO", &py_vector3, &py_vector3_pos)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    bulletphysics_Vector3Object *vector3_pos = (bulletphysics_Vector3Object *) py_vector3_pos;
    self->rigidBody->applyForce(*(vector3->vector), *(vector3_pos->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_applyCentralImpulse(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->applyCentralImpulse(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_applyTorque(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->applyTorque(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_applyTorqueImpulse(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->applyTorqueImpulse(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_applyImpulse(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    PyObject *py_vector3_pos = NULL;
    if (!PyArg_ParseTuple(args, "OO", &py_vector3, &py_vector3_pos)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    bulletphysics_Vector3Object *vector3_pos = (bulletphysics_Vector3Object *) py_vector3_pos;
    self->rigidBody->applyImpulse(*(vector3->vector), *(vector3_pos->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_setWorldTransform(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    bulletphysics_TransformObject *py_transform = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_transform)) {
        return NULL;
    }
    pybulletphysics_checktype(py_transform, Transform);
    self->rigidBody->setWorldTransform(*(py_transform->transform));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_getWorldTransform(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return new_pytransform_from_transform(self->rigidBody->getWorldTransform());
}

static PyObject *
RigidBody_setLinearVelocity(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->setLinearVelocity(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_setAngularVelocity(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_vector3 = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_vector3)) {
        return NULL;
    }

    bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
    self->rigidBody->setAngularVelocity(*(vector3->vector));

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_activate(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    PyObject *py_bool = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_bool)) {
        return NULL;
    }

	if (py_bool == Py_False || py_bool == Py_None) {
		self->rigidBody->activate(false);
	}
	else {
		self->rigidBody->activate(true);
	}

    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_getCenterOfMassTransform(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return new_pytransform_from_transform(self->rigidBody->getCenterOfMassTransform());
}

static PyObject *
RigidBody_setCenterOfMassTransform(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
	bulletphysics_TransformObject *py_transform = NULL;
    if (!PyArg_ParseTuple(args, "O", &py_transform)) {
        return NULL;
    }
	pybulletphysics_checktype(py_transform, Transform);
	self->rigidBody->setCenterOfMassTransform(*(py_transform->transform));
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_setActivationState(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
	int state = 0;
    if (!PyArg_ParseTuple(args, "i", &state)) {
        return NULL;
    }
    self->rigidBody->setActivationState(state);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_getActivationState(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return PyInt_FromLong(self->rigidBody->getActivationState());
}

static PyObject *
RigidBody_getOrientation(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return new_pyquaternion_from_quaternion(self->rigidBody->getOrientation());
}

static PyObject *
RigidBody_getLinearVelocity(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return new_pyvector3_from_vector(self->rigidBody->getLinearVelocity());
}

static PyObject *
RigidBody_getCollisionFlags(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return PyInt_FromLong(self->rigidBody->getCollisionFlags());
}

static PyObject *
RigidBody_setCollisionFlags(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    int flags = 0;
    if (!PyArg_ParseTuple(args, "i", &flags)) {
        return NULL;
    }
    self->rigidBody->setCollisionFlags(flags);
    Py_INCREF(Py_None);
    return Py_None;
}

static PyObject *
RigidBody_getMotionState(bulletphysics_RigidBodyObject *self, PyObject *args, PyObject *kwds) {
    return new_motionstate_from_motionstate(self->rigidBody->getMotionState());
}

static PyMethodDef RigidBody_methods[] = {
    {"applyCentralForce", (PyCFunction)RigidBody_applyCentralForce, METH_VARARGS, NULL },
    {"applyForce", (PyCFunction)RigidBody_applyForce, METH_VARARGS, NULL },
    {"applyCentralImpulse", (PyCFunction)RigidBody_applyCentralImpulse, METH_VARARGS, NULL },
    {"applyImpulse", (PyCFunction)RigidBody_applyImpulse, METH_VARARGS, NULL },
    {"setLinearVelocity", (PyCFunction)RigidBody_setLinearVelocity, METH_VARARGS, NULL },
    {"setAngularVelocity", (PyCFunction)RigidBody_setAngularVelocity, METH_VARARGS, NULL },
    {"activate", (PyCFunction)RigidBody_activate, METH_VARARGS, NULL },
    {"applyTorque", (PyCFunction)RigidBody_applyTorque, METH_VARARGS, NULL },
    {"getOrientation", (PyCFunction)RigidBody_getOrientation, METH_VARARGS, NULL },
    {"applyTorqueImpulse", (PyCFunction)RigidBody_applyTorqueImpulse, METH_VARARGS, NULL },
    {"getCenterOfMassTransform", (PyCFunction)RigidBody_getCenterOfMassTransform, METH_VARARGS, NULL },
    {"setCenterOfMassTransform", (PyCFunction)RigidBody_setCenterOfMassTransform, METH_VARARGS, NULL },
    {"getLinearVelocity", (PyCFunction)RigidBody_getLinearVelocity, METH_VARARGS, NULL },
    {"setActivationState", (PyCFunction)RigidBody_setActivationState, METH_VARARGS, NULL },
    {"getActivationState", (PyCFunction)RigidBody_getActivationState, METH_VARARGS, NULL },
    {"getCollisionFlags", (PyCFunction)RigidBody_getCollisionFlags, METH_VARARGS, NULL },
    {"setCollisionFlags", (PyCFunction)RigidBody_setCollisionFlags, METH_VARARGS, NULL },
    {"getMotionState", (PyCFunction)RigidBody_getMotionState, METH_VARARGS, NULL },
    {"getWorldTransform", (PyCFunction)RigidBody_setWorldTransform, METH_VARARGS, NULL },
    {"setWorldTransform", (PyCFunction)RigidBody_setWorldTransform, METH_VARARGS, NULL },

    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_RigidBody(PyObject *module) {
	bulletphysics_RigidBodyType.tp_methods = RigidBody_methods;
	bulletphysics_RigidBodyType.tp_dictoffset = offsetof(bulletphysics_RigidBodyObject, dict);
	bulletphysics_RigidBodyType.tp_new = RigidBody_new;

    if (PyType_Ready(&bulletphysics_RigidBodyType) < 0)
        return;

	Py_INCREF(&bulletphysics_RigidBodyType);

    PyModule_AddObject(module, "RigidBody", (PyObject *)&bulletphysics_RigidBodyType);
}
