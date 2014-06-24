from bulletphysics import *


broadphase = DbvtBroadphase()
collisionConfiguration = DefaultCollisionConfiguration()
dispatcher = CollisionDispatcher(collisionConfiguration)
solver = SequentialImpulseConstraintSolver()


world = DiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration)
world.setGravity( Vector3(0, -9.81, 0) )

ground = StaticPlaneShape(Vector3(0,1,0),1)
box0 = BoxShape(Vector3(10, 10, 10));
box1 = BoxShape(Vector3(10, 10, 10));


ground_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0,-10,0)) )
ground_rigidbody_info = RigidBodyConstructionInfo(0, ground_motionstate, ground, Vector3(0,0,0))
ground_rigidbody = RigidBody(ground_rigidbody_info)
world.addRigidBody(ground_rigidbody)
ground_rigidbody.name = "ground"

box0_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 100,0)) )
box1_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 100,0)) )
box_mass = 100
local_inertia = Vector3(0,0,0)
box0.calculateLocalInertia(box_mass, local_inertia)

box0_rigidbody_info = RigidBodyConstructionInfo(box_mass, box0_motionstate, box0, local_inertia)
box1_rigidbody_info = RigidBodyConstructionInfo(box_mass, box1_motionstate, box1, local_inertia)

box0_rigidbody = RigidBody(box0_rigidbody_info)
box0_rigidbody.name = "box0"
print box0_rigidbody.name
box1_rigidbody = RigidBody(box1_rigidbody_info)
box1_rigidbody.name = "box1"
print box1_rigidbody.name

world.addRigidBody(box0_rigidbody)
world.addRigidBody(box1_rigidbody)

box0_trans = Transform()
box1_trans = Transform()

def cb(world, ts):
    nm = world.getDispatcher().getNumManifolds()
    print "cb", nm
    for i in range(0, nm):
        manifold = world.getDispatcher().getManifoldByIndexInternal(i)
        print "body0", manifold.getBody0().name
        print "body1", manifold.getBody1().name
    print("hello", ts, world.getWorldUserInfo())

world.setInternalTickCallback(cb, 17)

for i in range(0, 300):
    world.stepSimulation(1/60.0, 10)
    box0_motionstate.getWorldTransform(box0_trans)
    box1_motionstate.getWorldTransform(box1_trans)
    print box0_trans.getOrigin().getY()
    print box1_trans.getOrigin().getY()


world.removeRigidBody(box0_rigidbody)
world.removeRigidBody(box1_rigidbody)
world.removeRigidBody(ground_rigidbody)
