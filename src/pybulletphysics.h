#include <Python.h>
#include <btBulletDynamicsCommon.h>

#define pybulletphysics_checktype(x, y) if (!PyObject_TypeCheck(x, &bulletphysics_ ## y ## Type)) {\
                PyErr_SetString(PyExc_TypeError, "expected a " #y "Type");\
                return NULL;\
        }\

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
void pybulletphysics_add_BoxShape(PyObject *);
void pybulletphysics_add_PersistentManifold(PyObject *);
void pybulletphysics_add_VehicleTuning(PyObject *);
void pybulletphysics_add_WheelInfo(PyObject *);

typedef struct {
        PyObject_HEAD
        btBroadphaseInterface *broadphase;
} bulletphysics_BroadphaseInterfaceObject;


typedef struct {
        PyObject_HEAD
        btCollisionConfiguration *configuration;
} bulletphysics_CollisionConfigurationObject;

typedef struct {
        PyObject_HEAD
        btPersistentManifold *manifold;
	int do_not_delete;
} bulletphysics_PersistentManifoldObject;
PyObject *new_pypersistentmanifold_from_persistentmanifold(btPersistentManifold *);

typedef struct {
        PyObject_HEAD
        btDispatcher *dispatcher;
	bulletphysics_CollisionConfigurationObject *collision_configuration;
} bulletphysics_DispatcherObject;


typedef struct {
        PyObject_HEAD
        btConstraintSolver *solver;
} bulletphysics_ConstraintSolverObject;

typedef struct {
        PyObject_HEAD
        btDynamicsWorld *world;
	bulletphysics_BroadphaseInterfaceObject *broadphase;	
	bulletphysics_CollisionConfigurationObject *collision_configuration;
	bulletphysics_DispatcherObject *dispatcher;
	bulletphysics_ConstraintSolverObject *solver;
	PyObject *callback;
	PyObject *userinfo;
} bulletphysics_DynamicsWorldObject;

typedef struct {
        PyObject_HEAD
        btVector3 *vector;
} bulletphysics_Vector3Object;
PyObject *new_pyvector3_from_vector(btVector3);

typedef struct {
        PyObject_HEAD
        btQuaternion *quaternion;
} bulletphysics_QuaternionObject;
PyObject *new_pyquaternion_from_quaternion(btQuaternion);

typedef struct {
        PyObject_HEAD
        btCollisionShape *shape;
} bulletphysics_CollisionShapeObject;

typedef struct {
        PyObject_HEAD
        btTransform *transform;
	bulletphysics_Vector3Object *origin;
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
	PyObject* dict;
} bulletphysics_RigidBodyObject;

typedef struct {
        PyObject_HEAD
        btRaycastVehicle::btVehicleTuning *tuning;
} bulletphysics_VehicleTuningObject;

typedef struct {
        PyObject_HEAD
        btWheelInfo *wheel;
} bulletphysics_WheelInfoObject;
