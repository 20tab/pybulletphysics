#include "pybulletphysics.h"

static void
Vector3_dealloc(bulletphysics_Vector3Object* self)
{
	if (self->vector)
        	delete(self->vector);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Vector3_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float x = 0.0;
	float y = 0.0;
	float z = 0.0;
	if (!PyArg_ParseTuple(args, "fff", &x, &y, &z)) {
        	return NULL;
    	}

        bulletphysics_Vector3Object *self = (bulletphysics_Vector3Object *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->vector = new btVector3(x, y, z);
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_Vector3Type = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.Vector3", /*tp_name*/
    sizeof(bulletphysics_Vector3Object), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Vector3_dealloc,    /*tp_dealloc*/
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
    "Vector3 object",           /* tp_doc */
};

PyObject *new_pyvector3_from_vector(btVector3 v) {
	bulletphysics_Vector3Object *py_vector3 = (bulletphysics_Vector3Object *)bulletphysics_Vector3Type.tp_alloc(&bulletphysics_Vector3Type, 0);
	if (py_vector3) {
		py_vector3->vector = new btVector3(v.getX(), v.getY(), v.getZ());
		Py_INCREF(py_vector3);
	}
	return (PyObject *)py_vector3;
}

static PyObject *
Vector3_rotate(bulletphysics_Vector3Object *self, PyObject *args, PyObject *kwds) {
	bulletphysics_Vector3Object *py_vector3 = NULL;
	float angle = 0.0;
	if (!PyArg_ParseTuple(args, "Of", &py_vector3, &angle)) {
                return NULL;
        }
	pybulletphysics_checktype(py_vector3, Vector3);
	return new_pyvector3_from_vector( self->vector->rotate(*(py_vector3->vector), angle) );
}

static PyObject *
Vector3_add(bulletphysics_Vector3Object *self, PyObject *py_vector3) {
	pybulletphysics_checktype(py_vector3, Vector3);
	return new_pyvector3_from_vector( *self->vector + *(((bulletphysics_Vector3Object *)py_vector3)->vector));
}

static PyObject *
Vector3_mul(bulletphysics_Vector3Object *self, PyObject *py_vector3) {
        pybulletphysics_checktype(py_vector3, Vector3);
        return new_pyvector3_from_vector( *self->vector * *(((bulletphysics_Vector3Object *)py_vector3)->vector));
}

static PyObject *
Vector3_getX(bulletphysics_Vector3Object *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->vector->getX());
}

static PyObject *
Vector3_getY(bulletphysics_Vector3Object *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->vector->getY());
}

static PyObject *
Vector3_getZ(bulletphysics_Vector3Object *self, PyObject *args, PyObject *kwds) {
        return PyFloat_FromDouble(self->vector->getZ());
}

static PyMethodDef Vector3_methods[] = {
    {"getX", (PyCFunction)Vector3_getX, METH_VARARGS, NULL },
    {"getY", (PyCFunction)Vector3_getY, METH_VARARGS, NULL },
    {"getZ", (PyCFunction)Vector3_getZ, METH_VARARGS, NULL },
    {"rotate", (PyCFunction)Vector3_rotate, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

PyNumberMethods Vector3_number_methods;

void pybulletphysics_add_Vector3(PyObject *module) {
	memset(&Vector3_number_methods, 0, sizeof(PyNumberMethods));
	bulletphysics_Vector3Type.tp_as_number = &Vector3_number_methods;

	Vector3_number_methods.nb_add = (binaryfunc)Vector3_add;
	Vector3_number_methods.nb_multiply = (binaryfunc)Vector3_mul;

	bulletphysics_Vector3Type.tp_methods = Vector3_methods;
	bulletphysics_Vector3Type.tp_new = Vector3_new;

        if (PyType_Ready(&bulletphysics_Vector3Type) < 0)
                return;	

	Py_INCREF(&bulletphysics_Vector3Type);

        PyModule_AddObject(module, "Vector3", (PyObject *)&bulletphysics_Vector3Type);
}
