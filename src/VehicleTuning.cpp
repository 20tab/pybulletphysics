#include "pybulletphysics.h"

static void
VehicleTuning_dealloc(bulletphysics_VehicleTuningObject* self)
{
        delete(self->tuning);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
VehicleTuning_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
        bulletphysics_VehicleTuningObject *self = (bulletphysics_VehicleTuningObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
                self->tuning = new btRaycastVehicle::btVehicleTuning();
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_VehicleTuningType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.VehicleTuning", /*tp_name*/
    sizeof(bulletphysics_VehicleTuningObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)VehicleTuning_dealloc,    /*tp_dealloc*/
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
    "VehicleTuning object",           /* tp_doc */
};

void pybulletphysics_add_VehicleTuning(PyObject *module) {
	bulletphysics_VehicleTuningType.tp_new = VehicleTuning_new;

        if (PyType_Ready(&bulletphysics_VehicleTuningType) < 0)
                return;	

	Py_INCREF(&bulletphysics_VehicleTuningType);

        PyModule_AddObject(module, "VehicleTuning", (PyObject *)&bulletphysics_VehicleTuningType);
}
