#include "pybulletphysics.h"

extern PyTypeObject bulletphysics_VehicleTuningType;
extern PyTypeObject bulletphysics_DefaultVehicleRaycasterType;
extern PyTypeObject bulletphysics_RigidBodyType;
extern PyTypeObject bulletphysics_Vector3Type;

static void
RaycastVehicle_dealloc(bulletphysics_RaycastVehicleObject* self)
{
	Py_DECREF(self->tuning);
	Py_DECREF(self->chassis);
	Py_DECREF(self->raycaster);
        delete(self->vehicle);
        self->ob_type->tp_free((PyObject*)self);
}

static PyObject*
RaycastVehicle_new(PyTypeObject *type, PyObject *args, PyObject *kwds)
{
	bulletphysics_VehicleTuningObject *py_tuning = NULL;
	bulletphysics_RigidBodyObject *py_chassis = NULL;
	bulletphysics_VehicleRaycasterObject *py_raycaster = NULL;

	if (!PyArg_ParseTuple(args, "OOO", &py_tuning, &py_chassis, &py_raycaster)) {
        	return NULL;
    	}

	if (!PyObject_TypeCheck(py_tuning, &bulletphysics_VehicleTuningType)) {
		PyErr_SetString(PyExc_TypeError, "expected a VehicleTuningType");
		return NULL;
	}

	if (!PyObject_TypeCheck(py_chassis, &bulletphysics_RigidBodyType)) {
		PyErr_SetString(PyExc_TypeError, "expected a RigidBodyType");
		return NULL;
	}

	if (!PyObject_TypeCheck(py_raycaster, &bulletphysics_DefaultVehicleRaycasterType)) {
		PyErr_SetString(PyExc_TypeError, "expected a DefaultVehicleRaycasterType");
		return NULL;
	}

        bulletphysics_RaycastVehicleObject *self = (bulletphysics_RaycastVehicleObject *)type->tp_alloc(type, 0);
        if (self != NULL) {
		self->vehicle = new btRaycastVehicle(*(py_tuning->tuning), py_chassis->rigidBody, py_raycaster->raycaster);
		self->tuning = py_tuning; Py_INCREF(self->tuning);
		self->chassis = py_chassis; Py_INCREF(self->chassis);
		self->raycaster = py_raycaster; Py_INCREF(self->raycaster);
        }
        return (PyObject *)self;
}

static PyObject *
RaycastVehicle_setBrake(bulletphysics_RaycastVehicleObject *self, PyObject *args, PyObject *kwds) {
        float brake = 0.0;
        int wheel = 0;
        if (!PyArg_ParseTuple(args, "fi", &brake, &wheel)) {
                return NULL;
        }
        self->vehicle->setBrake(brake, wheel);
        Py_INCREF(Py_None);
        return Py_None;
}


static PyObject *
RaycastVehicle_applyEngineForce(bulletphysics_RaycastVehicleObject *self, PyObject *args, PyObject *kwds) {
        float force = 0.0;
        int wheel = 0;
        if (!PyArg_ParseTuple(args, "fi", &force, &wheel)) {
                return NULL;
        }
        self->vehicle->applyEngineForce(force, wheel);
        Py_INCREF(Py_None);
        return Py_None;
}

static PyObject *
RaycastVehicle_setCoordinateSystem(bulletphysics_RaycastVehicleObject *self, PyObject *args, PyObject *kwds) {
        int right = 0;
        int up = 0;
        int forward = 0;
        if (!PyArg_ParseTuple(args, "iii", &right, &up, &forward)) {
                return NULL;
        }
        self->vehicle->setCoordinateSystem(right, up, forward);
        Py_INCREF(Py_None);
        return Py_None;
}


static PyObject *
RaycastVehicle_setSteeringValue(bulletphysics_RaycastVehicleObject *self, PyObject *args, PyObject *kwds) {
        float steering = 0.0;
	int wheel = 0;
	if (!PyArg_ParseTuple(args, "fi", &steering, &wheel)) {
                return NULL;
        }
	self->vehicle->setSteeringValue(steering, wheel);
	Py_INCREF(Py_None);
	return Py_None;
}

static PyObject *
RaycastVehicle_addWheel(bulletphysics_RaycastVehicleObject *self, PyObject *args, PyObject *kwds) {
	bulletphysics_Vector3Object *cpoint = NULL;
	bulletphysics_Vector3Object *direction = NULL;
	bulletphysics_Vector3Object *axle = NULL;
	float suspension = 0.0;
	float radius = 0.0;
	bulletphysics_VehicleTuningObject *tuning = NULL;
	PyObject *is_front_wheel = NULL;

	if (!PyArg_ParseTuple(args, "OOOffOO", &cpoint, &direction, &axle, &suspension, &radius, &tuning, &is_front_wheel)) {
                return NULL;
        }

        if (!PyObject_TypeCheck(cpoint, &bulletphysics_Vector3Type)) {
                PyErr_SetString(PyExc_TypeError, "expected a Vector3Type");
                return NULL;
        }

	if (!PyObject_TypeCheck(direction, &bulletphysics_Vector3Type)) {
                PyErr_SetString(PyExc_TypeError, "expected a Vector3Type");
                return NULL;
        }
	
	if (!PyObject_TypeCheck(axle, &bulletphysics_Vector3Type)) {
                PyErr_SetString(PyExc_TypeError, "expected a Vector3Type");
                return NULL;
        }

	if (!PyObject_TypeCheck(tuning, &bulletphysics_VehicleTuningType)) {
                PyErr_SetString(PyExc_TypeError, "expected a VehicleTuningType");
                return NULL;
        }

	self->vehicle->addWheel(*(cpoint->vector), *(direction->vector), *(axle->vector), suspension, radius, *(tuning->tuning), PyObject_IsTrue(is_front_wheel));

	Py_INCREF(Py_None);
        return Py_None;
	
}

static PyMethodDef RaycastVehicle_methods[] = {
    {"setSteeringValue", (PyCFunction)RaycastVehicle_setSteeringValue, METH_VARARGS, NULL },
    {"applyEngineForce", (PyCFunction)RaycastVehicle_applyEngineForce, METH_VARARGS, NULL },
    {"setBrake", (PyCFunction)RaycastVehicle_setBrake, METH_VARARGS, NULL },
    {"addWheel", (PyCFunction)RaycastVehicle_addWheel, METH_VARARGS, NULL },
    {"setCoordinateSystem", (PyCFunction)RaycastVehicle_setCoordinateSystem, METH_VARARGS, NULL },
    {NULL, NULL, 0, NULL}
};


PyTypeObject bulletphysics_RaycastVehicleType = {
    PyObject_HEAD_INIT(NULL)
    0,                         /*ob_size*/
    "bulletphysics.RaycastVehicle", /*tp_name*/
    sizeof(bulletphysics_RaycastVehicleObject), /*tp_basicsize*/
    0,                         /*tp_itemsize*/
    (destructor)RaycastVehicle_dealloc,    /*tp_dealloc*/
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
    "RaycastVehicle object",           /* tp_doc */
};

void pybulletphysics_add_RaycastVehicle(PyObject *module) {
	bulletphysics_RaycastVehicleType.tp_new = RaycastVehicle_new;
	bulletphysics_RaycastVehicleType.tp_methods = RaycastVehicle_methods;

        if (PyType_Ready(&bulletphysics_RaycastVehicleType) < 0)
                return;	

	Py_INCREF(&bulletphysics_RaycastVehicleType);

        PyModule_AddObject(module, "RaycastVehicle", (PyObject *)&bulletphysics_RaycastVehicleType);
}
