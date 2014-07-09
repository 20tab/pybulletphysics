from bulletphysics import *


broadphase = DbvtBroadphase()
collisionConfiguration = DefaultCollisionConfiguration()
dispatcher = CollisionDispatcher(collisionConfiguration)
solver = SequentialImpulseConstraintSolver()


world = DiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration)
world.setGravity( Vector3(0, -10, 0) )

ground = BoxShape(Vector3(100, 10, 100))
chassis = BoxShape(Vector3(10, 10, 20));


ground_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0,-10,0)) )
ground_rigidbody_info = RigidBodyConstructionInfo(0, ground_motionstate, ground, Vector3(0,0,0))
ground_rigidbody = RigidBody(ground_rigidbody_info)
world.addRigidBody(ground_rigidbody)
ground_rigidbody.name = "ground"

chassis_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 60,0)) )
chassis_mass = 100
local_inertia = Vector3(0,0,0)
chassis.calculateLocalInertia(chassis_mass, local_inertia)

chassis_rigidbody_info = RigidBodyConstructionInfo(chassis_mass, chassis_motionstate, chassis, local_inertia)

chassis_rigidbody = RigidBody(chassis_rigidbody_info)
chassis_rigidbody.name = "chassis"

tuning = VehicleTuning()
raycaster = DefaultVehicleRaycaster(world)
vehicle = RaycastVehicle(tuning, chassis_rigidbody, raycaster)

print vehicle

world.addRigidBody(chassis_rigidbody)
chassis_rigidbody.setActivationState(4)


world.addAction(vehicle)

vehicle.setCoordinateSystem(0, 1, 2)

# back left (0)
vehicle.addWheel(Vector3(-4, -3, -8), Vector3(0,-1, 0), Vector3(-1, 0, 0), 0.6, 1.0, tuning, False)
# back right (1)
vehicle.addWheel(Vector3(4, -3, -8), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.0, tuning, False)
# front left (2)
vehicle.addWheel(Vector3(-4, -3, 8), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.0, tuning, True)
# front right (3)
vehicle.addWheel(Vector3(4, -3, 8), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.0, tuning, True)


vehicle.applyEngineForce(1000, 0)
vehicle.applyEngineForce(1000, 1)
vehicle.applyEngineForce(1000, 2)
vehicle.applyEngineForce(1000, 3)

chassis_trans = Transform()

for i in range(0, 3000):
    vehicle.applyEngineForce(10000, 0)
    vehicle.applyEngineForce(10000, 1)
    vehicle.applyEngineForce(10000, 2)
    vehicle.applyEngineForce(10000, 3)
    vehicle.setBrake(0, 2)
    vehicle.setBrake(0, 3)
    world.stepSimulation(1/30.0, 10)
    chassis_motionstate.getWorldTransform(chassis_trans)
    origin = chassis_trans.getOrigin()
    print origin.getX(), origin.getY(), origin.getZ()
