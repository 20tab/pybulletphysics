#include "pybulletphysics.h"

static void
Transform_dealloc(bulletphysics_TransformObject* self)
{
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
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_TransformType = {
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

void pybulletphysics_add_Transform(PyObject *module) {
	bulletphysics_TransformType.tp_new = Transform_new;

        if (PyType_Ready(&bulletphysics_TransformType) < 0)
                return;	

	Py_INCREF(&bulletphysics_TransformType);

        PyModule_AddObject(module, "Transform", (PyObject *)&bulletphysics_TransformType);
}
