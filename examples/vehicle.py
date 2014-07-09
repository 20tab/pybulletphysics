from bulletphysics import *


broadphase = DbvtBroadphase()
collisionConfiguration = DefaultCollisionConfiguration()
dispatcher = CollisionDispatcher(collisionConfiguration)
solver = SequentialImpulseConstraintSolver()


world = DiscreteDynamicsWorld(dispatcher, broadphase, solver,collisionConfiguration)
world.setGravity( Vector3(0, -10, 0) )

ground = BoxShape(Vector3(1000, 10, 1000))
chassis = BoxShape(Vector3(10, 10, 20));


ground_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0,-50,0)) )
ground_rigidbody_info = RigidBodyConstructionInfo(0, ground_motionstate, ground, Vector3(0,0,0))
ground_rigidbody = RigidBody(ground_rigidbody_info)
world.addRigidBody(ground_rigidbody)
ground_rigidbody.name = "ground"

chassis_motionstate = DefaultMotionState( Transform(Quaternion(0,0,0,1), Vector3(0, 60,0)) )
chassis_mass = 1000
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
vehicle.addWheel(Vector3(-10, -4.5, -19), Vector3(0,-1, 0), Vector3(-1, 0, 0), 0.6, 1.5, tuning, False)
# back right (1)
vehicle.addWheel(Vector3(10, -4.5, -19), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.5, tuning, False)
# front left (2)
vehicle.addWheel(Vector3(-10, -4.5, 19), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.5, tuning, True)
# front right (3)
vehicle.addWheel(Vector3(10, -4.5, 19), Vector3(0, -1, 0), Vector3(-1, 0, 0), 0.6, 1.5, tuning, True)


chassis_trans = Transform()

for i in range(0, 300):
    vehicle.setSteeringValue(0, 2)
    vehicle.setSteeringValue(0, 3)

    vehicle.applyEngineForce(1000, 0)
    vehicle.applyEngineForce(1000, 1)
    vehicle.setBrake(0, 0)
    vehicle.setBrake(0, 1)

    world.stepSimulation(1/30.0, 1)
    chassis_motionstate.getWorldTransform(chassis_trans)
    origin = chassis_trans.getOrigin()
    print origin.getX(), origin.getY(), origin.getZ()
