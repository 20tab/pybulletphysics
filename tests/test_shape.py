import unittest
from bulletphysics import *

class ShapeTest(unittest.TestCase):

    def test_creation(self):
        compound = CompoundShape()
        box = BoxShape(Vector3(1.0,0.5,2.0))
        transform = Transform()
        transform.setIdentity()
        transform.setOrigin(Vector3(0, 1, 0))
        compound.addChildShape(transform, box)
        

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
