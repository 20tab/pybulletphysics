#include <Python.h>
#include <btBulletDynamicsCommon.h>

void pybulletphysics_add_DbvtBroadphase(PyObject *);
void pybulletphysics_add_DefaultCollisionConfiguration(PyObject *);
void pybulletphysics_add_CollisionDispatcher(PyObject *);
void pybulletphysics_add_SequentialImpulseConstraintSolver(PyObject *);
void pybulletphysics_add_DiscreteDynamicsWorld(PyObject *);
void pybulletphysics_add_Vector3(PyObject *);
void pybulletphysics_add_Quaternion(PyObject *);
void pybulletphysics_add_StaticPlaneShape(PyObject *);
void pybulletphysics_add_CollisionShape(PyObject *);
void pybulletphysics_add_SphereShape(PyObject *);
void pybulletphysics_add_Transform(PyObject *);
void pybulletphysics_add_DefaultMotionState(PyObject *);
void pybulletphysics_add_RigidBodyConstructionInfo(PyObject *);
void pybulletphysics_add_RigidBody(PyObject *);

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


typedef struct {
        PyObject_HEAD
        btSequentialImpulseConstraintSolver *solver;
} bulletphysics_SequentialImpulseConstraintSolverObject;

typedef struct {
        PyObject_HEAD
        btDiscreteDynamicsWorld *world;
} bulletphysics_DiscreteDynamicsWorldObject;

typedef struct {
        PyObject_HEAD
        btVector3 *vector;
} bulletphysics_Vector3Object;

typedef struct {
        PyObject_HEAD
        btQuaternion *quaternion;
} bulletphysics_QuaternionObject;

typedef struct {
        PyObject_HEAD
        btCollisionShape *shape;
} bulletphysics_CollisionShapeObject;

typedef struct {
        PyObject_HEAD
        btTransform *transform;
	PyObject *origin;
} bulletphysics_TransformObject;

typedef struct {
        PyObject_HEAD
        btDefaultMotionState *motionState;
} bulletphysics_DefaultMotionStateObject;

typedef struct {
        PyObject_HEAD
        btRigidBody::btRigidBodyConstructionInfo *constructionInfo;
} bulletphysics_RigidBodyConstructionInfoObject;

typedef struct {
        PyObject_HEAD
        btRigidBody *rigidBody;
} bulletphysics_RigidBodyObject;

