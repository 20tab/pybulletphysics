from bulletphysics import *

broadphase = DbvtBroadphase()
collisionConfiguration = DefaultCollisionConfiguration()
dispatcher = CollisionDispatcher(collisionConfiguration)

print dispatcher

solver = SequentialImpulseConstraintSolver()

world = DiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration)

world.setGravity( Vector3(0, 0, 0) )

print world

ground = StaticPlaneShape(Vector3(0,1,0),1)
box = BoxShape(Vector3(10, 10, 10));

print ground
print box

ground_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0,-10,0)) )

print ground_motionstate

# 0 is the mass
ground_rigidbody_info = RigidBodyConstructionInfo(0, ground_motionstate, ground, Vector3(0,0,0))

print ground_rigidbody_info

ground_rigidbody = RigidBody(ground_rigidbody_info)

print ground_rigidbody

world.addRigidBody(ground_rigidbody)

box_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 100,0)) )

box_mass = 1 

local_inertia = Vector3(0,0,0)

box.calculateLocalInertia(box_mass, local_inertia)

print local_inertia.getX()
print local_inertia.getY()
print local_inertia.getZ()

# 1 is the mass, the last vector is the Inertia
box_rigidbody_info = RigidBodyConstructionInfo(box_mass, box_motionstate, box, local_inertia)

box_rigidbody = RigidBody(box_rigidbody_info)

world.addRigidBody(box_rigidbody)

box_rigidbody.applyCentralForce( Vector3(0.0, 0.0, 200.0) )

trans = Transform()

for i in range(0, 30000):
    world.stepSimulation(1/60.0, 10)
    box_motionstate.getWorldTransform(trans)
    print trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()


world.removeRigidBody(box_rigidbody)
world.removeRigidBody(ground_rigidbody)
