import unittest
from bulletphysics import *

class WorldTest(unittest.TestCase):

    def setUp(self):
        collisionConfiguration = DefaultCollisionConfiguration()
        self.world = DiscreteDynamicsWorld( CollisionDispatcher(collisionConfiguration),
            DbvtBroadphase(), SequentialImpulseConstraintSolver(),
            collisionConfiguration)

    def test_gravity(self):
        self.assertRaises(TypeError, self.world.setGravity, True)
        self.assertIsNone(self.world.setGravity(Vector3(0.0, -9.81, 0.0)))

    def test_remove_none_rigidbody(self):
        self.assertRaises(TypeError, self.world.removeRigidBody, None)

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
