import unittest
from bulletphysics import *

class VehicleTest(unittest.TestCase):

    def setUp(self):
        collisionConfiguration = DefaultCollisionConfiguration()
        self.world = DiscreteDynamicsWorld( CollisionDispatcher(collisionConfiguration),
            DbvtBroadphase(), SequentialImpulseConstraintSolver(),
            collisionConfiguration)
        self.tuning = VehicleTuning()
        self.raycaster = DefaultVehicleRaycaster(self.world)
        box = BoxShape(Vector3(10, 10, 10));
        q = Quaternion(0,0,0,1)
        v = Vector3(0,-1,0)
        t = Transform(q, v)
        motionstate = DefaultMotionState( t )
        construction_info = RigidBodyConstructionInfo(0, motionstate, box, Vector3(0,0,0))
        self.chassis = RigidBody( construction_info )

    def test_wheel(self):
        vehicle = RaycastVehicle(self.tuning, self.chassis, self.raycaster)
        vehicle.addWheel(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 4.0, self.tuning, True)
        vehicle.addWheel(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 4.0, self.tuning, True)
        vehicle.addWheel(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 4.0, self.tuning, False)
        vehicle.addWheel(Vector3(0, 0, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0, 4.0, self.tuning, False)

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
