from bulletphysics import *

broadphase = DbvtBroadphase()
collisionConfiguration = DefaultCollisionConfiguration()
dispatcher = CollisionDispatcher(collisionConfiguration)

print dispatcher

solver = SequentialImpulseConstraintSolver()

world = DiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration)

world.setGravity( Vector3(0, -10, 0) )

print world

ground = StaticPlaneShape(Vector3(0,1,0),1)
fall = SphereShape(1);

print ground
print fall

q = Quaternion(0,0,0,1)
print q
v = Vector3(0,-1,0)
print v

t = Transform(q, v)

print t

ground_motionstate = DefaultMotionState( t )

print ground_motionstate

# 0 is the mass
ground_rigidbody_info = RigidBodyConstructionInfo(0, ground_motionstate, ground, Vector3(0,0,0))

print ground_rigidbody_info

ground_rigidbody = RigidBody(ground_rigidbody_info)

print ground_rigidbody

world.addRigidBody(ground_rigidbody)

fall_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 50,0)) )

fall.calculateLocalInertia(1, Vector3(0,0,0))

# 1 is the mass, the last vector is the Inertia (???)
fall_rigidbody_info = RigidBodyConstructionInfo(1, fall_motionstate, fall, Vector3(0,0,0))

fall_rigidbody = RigidBody(fall_rigidbody_info)

world.addRigidBody(fall_rigidbody)

trans = Transform()

for i in range(0, 300):
    world.stepSimulation(1/60.0, 10)

    fall_rigidbody.getMotionState().getWorldTransform(transform)

    print trans.getOrigin().y


world.removeRigidBody(fall_rigidbody)
world.removeRigidBody(ground_rigidbody)
