#include "pybulletphysics.h"

static void
RigidBodyConstructionInfo_dealloc(bulletphysics_RigidBodyConstructionInfoObject* self)
{
        delete(self->constructionInfo);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
RigidBodyConstructionInfo_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	float mass = 0.0;
	PyObject *py_motionState = NULL;
	PyObject *py_shape = NULL;
	PyObject *py_vector3 = NULL;

	if (!PyArg_ParseTuple(args, "fOOO", &mass, &py_motionState, &py_shape, &py_vector3)) {
        	return NULL;
    	}

        bulletphysics_RigidBodyConstructionInfoObject *self = (bulletphysics_RigidBodyConstructionInfoObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_DefaultMotionStateObject *motionState = (bulletphysics_DefaultMotionStateObject *) py_motionState;
		bulletphysics_CollisionShapeObject *shape = (bulletphysics_CollisionShapeObject *) py_shape;
		bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
                self->constructionInfo = new btRigidBody::btRigidBodyConstructionInfo(mass, motionState->motionState, shape->shape, *(vector3->vector));
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_RigidBodyConstructionInfoType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.RigidBodyConstructionInfo", /*tp_name*/
    sizeof(bulletphysics_RigidBodyConstructionInfoObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)RigidBodyConstructionInfo_dealloc,    /*tp_dealloc*/
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
    "RigidBodyConstructionInfo object",           /* tp_doc */
};

static PyObject*
RigidBodyConstructionInfo_m_friction_get(bulletphysics_RigidBodyConstructionInfoObject* self, void *closure) {
	return PyFloat_FromDouble(self->constructionInfo->m_friction);
}

static int
RigidBodyConstructionInfo_m_friction_set(bulletphysics_RigidBodyConstructionInfoObject* self, PyObject *value, void *closure) {
	if (!PyFloat_Check(value)) {
		PyErr_SetString(PyExc_TypeError,
                    "float expected");
			return -1;
	}	
	self->constructionInfo->m_friction = PyFloat_AsDouble(value);
	return 0;
}

static PyGetSetDef RigidBodyConstructionInfo_getseters[] = {
	{"m_friction", (getter)RigidBodyConstructionInfo_m_friction_get, (setter)RigidBodyConstructionInfo_m_friction_set, NULL, NULL},
	{NULL, NULL, NULL, NULL, NULL}
};


void pybulletphysics_add_RigidBodyConstructionInfo(PyObject *module) {
	bulletphysics_RigidBodyConstructionInfoType.tp_new = RigidBodyConstructionInfo_new;
	bulletphysics_RigidBodyConstructionInfoType.tp_getset = RigidBodyConstructionInfo_getseters;

        if (PyType_Ready(&bulletphysics_RigidBodyConstructionInfoType) < 0)
                return;	

	Py_INCREF(&bulletphysics_RigidBodyConstructionInfoType);

        PyModule_AddObject(module, "RigidBodyConstructionInfo", (PyObject *)&bulletphysics_RigidBodyConstructionInfoType);
}
