#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_Vector3Type;
extern PyTypeObject bulletphysics_QuaternionType;

static void
Transform_dealloc(bulletphysics_TransformObject* self)
{
	// vector will be freed by the transform
	self->origin->vector = NULL;
	Py_DECREF(self->origin);
        delete(self->transform);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
Transform_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_quaternion = NULL;
	PyObject *py_vector3 = NULL;

	if (!PyArg_ParseTuple(args, "|OO", &py_quaternion, &py_vector3)) {
        	return NULL;
    	}

        bulletphysics_TransformObject *self = (bulletphysics_TransformObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		if (py_quaternion && py_vector3) {
			bulletphysics_QuaternionObject *quaternion = (bulletphysics_QuaternionObject *) py_quaternion;
			bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
                	self->transform = new btTransform(*(quaternion->quaternion), *(vector3->vector));
		}
		else {
			self->transform = new btTransform();
		}
		// optimization: map a new Vector3() object to the origin
		PyObject *argList = Py_BuildValue("fff", 0.0, 0.0, 0.0);
		PyObject *py_origin = PyObject_CallObject((PyObject *) &bulletphysics_Vector3Type, argList);
		Py_DECREF(argList);
		self->origin = (bulletphysics_Vector3Object *) py_origin;
		// delete the original vector
		delete(self->origin->vector);
		self->origin->vector = &self->transform->getOrigin();
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_TransformType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.Transform", /*tp_name*/
    sizeof(bulletphysics_TransformObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)Transform_dealloc,    /*tp_dealloc*/
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
    "Transform object",           /* tp_doc */
};

static PyObject *
Transform_getOrigin(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	Py_INCREF(self->origin);
        return (PyObject *) self->origin;
}

static PyObject *
Transform_getRotation(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	btQuaternion r = self->transform->getRotation();
	PyObject *argList = Py_BuildValue("ffff", r.getX(), r.getY(), r.getZ(), r.getW());
        PyObject *py_q = PyObject_CallObject((PyObject *) &bulletphysics_QuaternionType, argList);
        Py_DECREF(argList);
        return py_q;
}

static PyObject *
Transform_setIdentity(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	self->transform->setIdentity();
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Transform_setRotation(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	bulletphysics_QuaternionObject *py_quaternion = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_quaternion)) {
                return NULL;
        }
	pybulletphysics_checktype(py_quaternion, Quaternion);	
	self->transform->setRotation(*(py_quaternion->quaternion));
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Transform_setOrigin(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	bulletphysics_Vector3Object *py_vector = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_vector)) {
                return NULL;
        }
	pybulletphysics_checktype(py_vector, Vector3);	
	self->transform->setOrigin(*(py_vector->vector));
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
Transform_getOpenGLMatrix(bulletphysics_TransformObject *self, PyObject *args, PyObject *kwds) {
	PyObject *py_list = NULL;
	if (!PyArg_ParseTuple(args, "O", &py_list)) {
                return NULL;
        }

	if (!PyList_Check(py_list) || PyList_Size(py_list) < 16) {
		PyErr_SetString(PyExc_TypeError, "expected a 16-element list");
                return NULL;
	}

	btScalar m[16];
	self->transform->getOpenGLMatrix(m);
	int i;
	for(i=0;i<16;i++) {
		PyList_SetItem(py_list, i, PyFloat_FromDouble(m[i]));
	}

	Py_INCREF(Py_None);
	return Py_None;
}

static PyMethodDef Transform_methods[] = {
    {"getOrigin", (PyCFunction)Transform_getOrigin, METH_VARARGS, NULL },
    {"setOrigin", (PyCFunction)Transform_setOrigin, METH_VARARGS, NULL },
    {"getRotation", (PyCFunction)Transform_getRotation, METH_VARARGS, NULL },
    {"getOpenGLMatrix", (PyCFunction)Transform_getOpenGLMatrix, METH_VARARGS, NULL },
    {"setIdentity", (PyCFunction)Transform_setIdentity, METH_VARARGS, NULL },
    {"setRotation", (PyCFunction)Transform_setRotation, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_Transform(PyObject *module) {
	bulletphysics_TransformType.tp_methods = Transform_methods;
	bulletphysics_TransformType.tp_new = Transform_new;

        if (PyType_Ready(&bulletphysics_TransformType) < 0)
                return;	

	Py_INCREF(&bulletphysics_TransformType);

        PyModule_AddObject(module, "Transform", (PyObject *)&bulletphysics_TransformType);
}
