import unittest

import test_world
import test_vector3
import test_transform
import test_quaternion
import test_rigidbody

def test_suite():
    suite = unittest.TestSuite()
    suite.addTest(test_world.test_suite())
    suite.addTest(test_vector3.test_suite())
    suite.addTest(test_transform.test_suite())
    suite.addTest(test_quaternion.test_suite())
    suite.addTest(test_rigidbody.test_suite())
    return suite

if __name__ == '__main__':
    unittest.main(defaultTest='test_suite')
