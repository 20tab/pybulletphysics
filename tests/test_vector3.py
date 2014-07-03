import unittest
from bulletphysics import *

class Vector3Test(unittest.TestCase):

    def setUp(self):
        self.vector = Vector3(1.0, 2.0, 3.0)

    def test_xyz(self):
        v = Vector3(0.0, 0.1, 0.2)
        self.assertEqual(0.0, round(v.getX(), 2))
        self.assertEqual(0.1, round(v.getY(), 2))
        self.assertEqual(0.2, round(v.getZ(), 2))

    def test_add(self):
        self.assertRaises(TypeError, self.vector.__add__, False)
        v = self.vector + Vector3(0.0, 0.1, 0.2)
        self.assertEqual(1.0, round(v.getX(), 2))
        self.assertEqual(2.1, round(v.getY(), 2))
        self.assertEqual(3.2, round(v.getZ(), 2))

    def test_mul(self):
        self.assertRaises(TypeError, self.vector.__mul__, False)
        v = self.vector * Vector3(0.0, 0.1, 0.2)
        self.assertEqual(0.0, round(v.getX(), 2))
        self.assertEqual(0.2, round(v.getY(), 2))
        self.assertEqual(0.6, round(v.getZ(), 2))

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
