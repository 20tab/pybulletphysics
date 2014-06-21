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

static PyMethodDef RigidBody_methods[] = {
    {"applyCentralForce", (PyCFunction)RigidBody_applyCentralForce, METH_VARARGS, NULL },
    {"applyForce", (PyCFunction)RigidBody_applyForce, METH_VARARGS, NULL },
    {"applyCentralImpulse", (PyCFunction)RigidBody_applyCentralImpulse, METH_VARARGS, NULL },
    {"applyImpulse", (PyCFunction)RigidBody_applyImpulse, METH_VARARGS, NULL },
    {"setLinearVelocity", (PyCFunction)RigidBody_setLinearVelocity, METH_VARARGS, NULL },
    {"setAngularVelocity", (PyCFunction)RigidBody_setAngularVelocity, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_RigidBody(PyObject *module) {
	bulletphysics_RigidBodyType.tp_methods = RigidBody_methods;
	bulletphysics_RigidBodyType.tp_new = RigidBody_new;

        if (PyType_Ready(&bulletphysics_RigidBodyType) < 0)
                return;	

	Py_INCREF(&bulletphysics_RigidBodyType);

        PyModule_AddObject(module, "RigidBody", (PyObject *)&bulletphysics_RigidBodyType);
}
