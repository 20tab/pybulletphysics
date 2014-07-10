#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_TransformType;

static PyObject*
CompoundShape_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_CollisionShapeObject *self = (bulletphysics_CollisionShapeObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->shape = new btCompoundShape();
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_CompoundShapeType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.CompoundShape", /*tp_name*/
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
    "CompoundShape object",           /* tp_doc */
};

extern PyTypeObject bulletphysics_CollisionShapeType;

static PyObject *
CompoundShape_addChildShape(bulletphysics_CollisionShapeObject *self, PyObject *args, PyObject *kwds) {
        bulletphysics_TransformObject *py_transform = NULL;
        bulletphysics_CollisionShapeObject *py_shape = NULL;
        if (!PyArg_ParseTuple(args, "OO", &py_transform, &py_shape)) {
                return NULL;
        }
        pybulletphysics_checktype(py_transform, Transform);
        pybulletphysics_checktype(py_shape, CollisionShape);
	btCompoundShape *bcs = ( btCompoundShape *) self->shape;
        bcs->addChildShape(*(py_transform->transform), py_shape->shape);
        Py_INCREF(Py_None);
        return Py_None;
}


static PyMethodDef CompoundShape_methods[] = {
    {"addChildShape", (PyCFunction)CompoundShape_addChildShape, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};

void pybulletphysics_add_CompoundShape(PyObject *module) {
	bulletphysics_CompoundShapeType.tp_base = &bulletphysics_CollisionShapeType;
	bulletphysics_CompoundShapeType.tp_methods = CompoundShape_methods;
	bulletphysics_CompoundShapeType.tp_new = CompoundShape_new;

        if (PyType_Ready(&bulletphysics_CompoundShapeType) < 0)
                return;	

	Py_INCREF(&bulletphysics_CompoundShapeType);

        PyModule_AddObject(module, "CompoundShape", (PyObject *)&bulletphysics_CompoundShapeType);
}
