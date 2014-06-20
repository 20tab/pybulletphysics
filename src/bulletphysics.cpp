#include "pybulletphysics.h"

static PyMethodDef bulletphysicsMethods[] = {
	{NULL, NULL, 0, NULL}
};

PyMODINIT_FUNC
initbulletphysics(void)
{
	PyObject *m = Py_InitModule("bulletphysics", bulletphysicsMethods);
	pybulletphysics_add_DbvtBroadphase(m);
	pybulletphysics_add_DefaultCollisionConfiguration(m);
	pybulletphysics_add_CollisionDispatcher(m);
}
