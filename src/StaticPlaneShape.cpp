#include "pybulletphysics.h"

static PyObject*
StaticPlaneShape_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	PyObject *py_vector3 = NULL;
	float planeConstant = 0;
	if (!PyArg_ParseTuple(args, "Of", &py_vector3, &planeConstant)) {
        	return NULL;
    	}

        bulletphysics_CollisionShapeObject *self = (bulletphysics_CollisionShapeObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		bulletphysics_Vector3Object *vector3 = (bulletphysics_Vector3Object *) py_vector3;
                self->shape = new btStaticPlaneShape(*(vector3->vector), planeConstant );
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_StaticPlaneShapeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.StaticPlaneShape", /*tp_name*/
    sizeof(bulletphysics_CollisionShapeObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    0,				/*tp_dealloc*/
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
    "StaticPlaneShape object",           /* tp_doc */
};

extern PyTypeObject bulletphysics_CollisionShapeType;

void pybulletphysics_add_StaticPlaneShape(PyObject *module) {
	bulletphysics_StaticPlaneShapeType.tp_base = &bulletphysics_CollisionShapeType;
	bulletphysics_StaticPlaneShapeType.tp_new = StaticPlaneShape_new;

        if (PyType_Ready(&bulletphysics_StaticPlaneShapeType) < 0)
                return;	

	Py_INCREF(&bulletphysics_StaticPlaneShapeType);

        PyModule_AddObject(module, "StaticPlaneShape", (PyObject *)&bulletphysics_StaticPlaneShapeType);
}
