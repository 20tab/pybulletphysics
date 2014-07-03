import unittest
from bulletphysics import *

class TransformTest(unittest.TestCase):

    def setUp(self):
        self.transform = Transform( Quaternion(0.0, 1.0, 2.0, 1.0), Vector3(0.0, 1.1, 2.2))

    def test_opengl(self):
        matrix = [0.0] * 5
        self.assertRaises(TypeError, self.transform.getOpenGLMatrix, matrix)
        matrix = [0.0] * 16
        self.transform.getOpenGLMatrix(matrix)
        self.assertEqual(-0.67, round(matrix[0], 2))

    def test_rotation(self):
        self.transform.setIdentity()
        q = Quaternion(1.0, 2.0, 3.0, 4.0)
        self.transform.setRotation(q)
        q = self.transform.getRotation()
        self.assertEqual(0.2, round(q.getX(),1))
        self.assertEqual(0.4, round(q.getY(),1))
        self.assertEqual(0.5, round(q.getZ(),1))
        self.assertEqual(0.7, round(q.getW(),1))

def test_suite():
    return unittest.TestLoader().loadTestsFromName(__name__)

if __name__ == "__main__":
    unittest.main()
