#include "pybulletphysics.h"

static void
WheelInfo_dealloc(bulletphysics_WheelInfoObject* self)
{
        delete(self->wheel);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
WheelInfo_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_WheelInfoObject *self = (bulletphysics_WheelInfoObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		btWheelInfoConstructionInfo ci;
                self->wheel = new btWheelInfo(ci);
        }
        return (PyObject *)self;
}

static PyTypeObject bulletphysics_WheelInfoType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.WheelInfo", /*tp_name*/
    sizeof(bulletphysics_WheelInfoObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)WheelInfo_dealloc,    /*tp_dealloc*/
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
    "WheelInfo object",           /* tp_doc */
};

PyObject *new_pywheelinfo_from_wheelinfo(btWheelInfo *wheel) {
        bulletphysics_WheelInfoObject *py_wheel = (bulletphysics_WheelInfoObject *)bulletphysics_WheelInfoType.tp_alloc(&bulletphysics_WheelInfoType, 0);
        if (py_wheel) {
                py_wheel->wheel = wheel;
                Py_INCREF(py_wheel);
        }
        return (PyObject *)py_wheel;
}

void pybulletphysics_add_WheelInfo(PyObject *module) {
	bulletphysics_WheelInfoType.tp_new = WheelInfo_new;

        if (PyType_Ready(&bulletphysics_WheelInfoType) < 0)
                return;	

	Py_INCREF(&bulletphysics_WheelInfoType);

        PyModule_AddObject(module, "WheelInfo", (PyObject *)&bulletphysics_WheelInfoType);
}
