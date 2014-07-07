#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_DiscreteDynamicsWorldType;

static void
DefaultVehicleRaycaster_dealloc(bulletphysics_VehicleRaycasterObject* self)
{
	Py_DECREF(self->world);
        delete(self->raycaster);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
DefaultVehicleRaycaster_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	bulletphysics_DynamicsWorldObject *py_world = NULL;

	if (!PyArg_ParseTuple(args, "O", &py_world)) {
        	return NULL;
    	}

	if (!PyObject_TypeCheck(py_world, &bulletphysics_DiscreteDynamicsWorldType)) {
		PyErr_SetString(PyExc_TypeError, "expected a DiscreteDynamicsWorldType");
		return NULL;
	}

        bulletphysics_VehicleRaycasterObject *self = (bulletphysics_VehicleRaycasterObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		self->raycaster = new btDefaultVehicleRaycaster(py_world->world);
		self->world = py_world; Py_INCREF(self->world);
        }
        return (PyObject *)self;
}

PyTypeObject bulletphysics_DefaultVehicleRaycasterType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.DefaultVehicleRaycaster", /*tp_name*/
    sizeof(bulletphysics_VehicleRaycasterObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)DefaultVehicleRaycaster_dealloc,    /*tp_dealloc*/
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
    "DefaultVehicleRaycaster object",           /* tp_doc */
};

void pybulletphysics_add_DefaultVehicleRaycaster(PyObject *module) {
	bulletphysics_DefaultVehicleRaycasterType.tp_new = DefaultVehicleRaycaster_new;

        if (PyType_Ready(&bulletphysics_DefaultVehicleRaycasterType) < 0)
                return;	

	Py_INCREF(&bulletphysics_DefaultVehicleRaycasterType);

        PyModule_AddObject(module, "DefaultVehicleRaycaster", (PyObject *)&bulletphysics_DefaultVehicleRaycasterType);
}
