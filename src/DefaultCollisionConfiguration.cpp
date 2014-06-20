#include "pybulletphysics.h"

static void
DefaultCollisionConfiguration_dealloc(bulletphysics_DefaultCollisionConfigurationObject* self)
{
        delete(self->configuration);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DefaultCollisionConfiguration_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_DefaultCollisionConfigurationObject *self = (bulletphysics_DefaultCollisionConfigurationObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->configuration = new btDefaultCollisionConfiguration();
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_DefaultCollisionConfigurationType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DefaultCollisionConfiguration", /*tp_name*/
    sizeof(bulletphysics_DefaultCollisionConfigurationObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)DefaultCollisionConfiguration_dealloc,    /*tp_dealloc*/
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
    "DefaultCollisionConfiguration object",           /* tp_doc */
};

void pybulletphysics_add_DefaultCollisionConfiguration(PyObject *module) {
	bulletphysics_DefaultCollisionConfigurationType.tp_new = DefaultCollisionConfiguration_new;

        if (PyType_Ready(&bulletphysics_DefaultCollisionConfigurationType) < 0)
                return;	

	Py_INCREF(&bulletphysics_DefaultCollisionConfigurationType);

        PyModule_AddObject(module, "DefaultCollisionConfiguration", (PyObject *)&bulletphysics_DefaultCollisionConfigurationType);
}
