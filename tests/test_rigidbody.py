import unittest
from bulletphysics import *

class RigidBodyTest(unittest.TestCase):

    def setUp(self):
        sphere = SphereShape(1);
        q = Quaternion(0,0,0,1)
        v = Vector3(0,-1,0)
        t = Transform(q, v)
        motionstate = DefaultMotionState( t )
        construction_info = RigidBodyConstructionInfo(0, motionstate, sphere, Vector3(0,0,0))
        self.body = RigidBody( construction_info )

    def test_linear_velocity(self):
        self.body.setLinearVelocity(Vector3(1.0, 2.0, 0.0))
        v = self.body.getLinearVelocity()
        self.assertEqual(1.0, v.getX())
        self.assertEqual(2.0, v.getY())
        self.assertEqual(0.0, v.getZ())

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
