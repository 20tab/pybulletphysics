#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_Vector3Type;

static void
Quaternion_dealloc(bulletphysics_QuaternionObject* self)
{
        delete(self->quaternion);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Quaternion_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	float w = 0.0;
	if (!PyArg_ParseTuple(args, "ffff", &x, &y, &z, &w)) {
        	return NULL;
    	}

        bulletphysics_QuaternionObject *self = (bulletphysics_QuaternionObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->quaternion = new btQuaternion(x, y, z, w);
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_QuaternionType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.Quaternion", /*tp_name*/
    sizeof(bulletphysics_QuaternionObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Quaternion_dealloc,    /*tp_dealloc*/
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
    Py_TPFLAGS_DEFAULT|Py_TPFLAGS_BASETYPE|Py_TPFLAGS_CHECKTYPES, /*tp_flags*/
    "Quaternion object",           /* tp_doc */
};

PyObject *new_pyquaternion_from_quaternion(btQuaternion q) {
        bulletphysics_QuaternionObject *py_quaternion = (bulletphysics_QuaternionObject *)bulletphysics_QuaternionType.tp_alloc(&bulletphysics_QuaternionType, 0);
        if (py_quaternion) {
                py_quaternion->quaternion = new btQuaternion(q.getX(), q.getY(), q.getZ(), q.getW());
                Py_INCREF(py_quaternion);
        }
        return (PyObject *)py_quaternion;
}

static PyObject *
Quaternion_getX(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->quaternion->getX());
}

static PyObject *
Quaternion_getY(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->quaternion->getY());
}

static PyObject *
Quaternion_getZ(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->quaternion->getZ());
}

static PyObject *
Quaternion_getW(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->quaternion->getW());
}

static PyObject *
Quaternion_getAxis(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
	return new_pyvector3_from_vector(self->quaternion->getAxis());
}

static PyObject *
Quaternion_getAngle(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
	return PyFloat_FromDouble(self->quaternion->getAngle());
}

static PyObject *
Quaternion_setRotation(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        bulletphysics_Vector3Object *py_vector3 = NULL;
        float angle = 0.0;
        if (!PyArg_ParseTuple(args, "Of", &py_vector3, &angle)) {
                return NULL;
        }
        pybulletphysics_checktype(py_vector3, Vector3);
	self->quaternion->setRotation(*(py_vector3->vector), angle);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Quaternion_quatRotate(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
        bulletphysics_QuaternionObject *py_quaternion = NULL;
        bulletphysics_Vector3Object *py_vector3 = NULL;
        if (!PyArg_ParseTuple(args, "OO", &py_quaternion, &py_vector3)) {
                return NULL;
        }
        pybulletphysics_checktype(py_quaternion, Quaternion);
        pybulletphysics_checktype(py_vector3, Vector3);
	return new_pyvector3_from_vector(quatRotate(*(py_quaternion->quaternion), *(py_vector3->vector)));
}

static PyObject *
Quaternion_setEuler(bulletphysics_QuaternionObject *self, PyObject *args, PyObject *kwds) {
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
        if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)) {
                return NULL;
        }
        self->quaternion->setEuler(x, y, z);
        Py_INCREF(Py_None);
        return Py_None;
}


static PyMethodDef Quaternion_methods[] = {
    {"getX", (PyCFunction)Quaternion_getX, METH_VARARGS, NULL },
    {"getY", (PyCFunction)Quaternion_getY, METH_VARARGS, NULL },
    {"getZ", (PyCFunction)Quaternion_getZ, METH_VARARGS, NULL },
    {"getW", (PyCFunction)Quaternion_getW, METH_VARARGS, NULL },
    {"getAxis", (PyCFunction)Quaternion_getAxis, METH_VARARGS, NULL },
    {"getAngle", (PyCFunction)Quaternion_getAngle, METH_VARARGS, NULL },
    {"setRotation", (PyCFunction)Quaternion_setRotation, METH_VARARGS, NULL },
    {"setEuler", (PyCFunction)Quaternion_setEuler, METH_VARARGS, NULL },
    {"quatRotate", (PyCFunction)Quaternion_quatRotate, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

static PyObject *
Quaternion_add(bulletphysics_QuaternionObject *self, PyObject *py_quaternion) {
        pybulletphysics_checktype(py_quaternion, Quaternion);
        return new_pyquaternion_from_quaternion( *self->quaternion + *(((bulletphysics_QuaternionObject *)py_quaternion)->quaternion));
}

static PyObject *
Quaternion_mul(bulletphysics_QuaternionObject *self, PyObject *py_q_or_t) {
	if (PyObject_TypeCheck(py_q_or_t, &bulletphysics_Vector3Type)) {
        	return new_pyquaternion_from_quaternion( *self->quaternion * *(((bulletphysics_Vector3Object *)py_q_or_t)->vector));
	}
        pybulletphysics_checktype(py_q_or_t, Quaternion);
        return new_pyquaternion_from_quaternion( *self->quaternion * *(((bulletphysics_QuaternionObject *)py_q_or_t)->quaternion));
}

PyNumberMethods Quaternion_number_methods;

void pybulletphysics_add_Quaternion(PyObject *module) {
	memset(&Quaternion_number_methods, 0, sizeof(PyNumberMethods));
        bulletphysics_QuaternionType.tp_as_number = &Quaternion_number_methods;

        Quaternion_number_methods.nb_add = (binaryfunc)Quaternion_add;
        Quaternion_number_methods.nb_multiply = (binaryfunc)Quaternion_mul;

	bulletphysics_QuaternionType.tp_methods = Quaternion_methods;
	bulletphysics_QuaternionType.tp_new = Quaternion_new;

        if (PyType_Ready(&bulletphysics_QuaternionType) < 0)
                return;	

	Py_INCREF(&bulletphysics_QuaternionType);

        PyModule_AddObject(module, "Quaternion", (PyObject *)&bulletphysics_QuaternionType);
}
