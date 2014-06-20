#include <Python.h>
#include <btBulletDynamicsCommon.h>

void pybulletphysics_add_DbvtBroadphase(PyObject *);
void pybulletphysics_add_DefaultCollisionConfiguration(PyObject *);
void pybulletphysics_add_CollisionDispatcher(PyObject *);

typedef struct {
        PyObject_HEAD
        btBroadphaseInterface *broadphase;
} bulletphysics_DbvtBroadphaseObject;


typedef struct {
        PyObject_HEAD
        btDefaultCollisionConfiguration *configuration;
} bulletphysics_DefaultCollisionConfigurationObject;

typedef struct {
        PyObject_HEAD
        btCollisionDispatcher *dispatcher;
} bulletphysics_CollisionDispatcherObject;
